// ============================
// 文件: threadmanager.cc
// 说明：ThreadManager 的实现（最终教学版）
// 核心并发模型：单生产者-多消费者，共享任务队列 + 全局锁保护。
// 所有对外接口均加锁，WorkerLoop 内部在取任务时加锁，执行时释放锁，保证高并发吞吐。
// 教学重点：
//   - 析构函数的三阶段清理（停止信号 → 等待线程退出 → 清理残留任务）
//   - 任务家族的顺序性控制（pending + nextSeq 机制）
//   - Flush 与 Sync 的实现差异
//   - 原子计数器与条件变量的配合使用
// ============================
#include "threadmanager.h"
#include <print> // C++23 标准输出（若不支持可替换为 <iostream> + std::cout）

// 构造函数：启动指定数量的工作线程
ThreadManager::ThreadManager(const std::string& name, std::size_t numThreads)
    : m_name(name)
    , m_numThreads(numThreads == 0 ? 1 : numThreads) // 至少1个线程
{
    // 预留空间，避免 vector 扩容影响性能
    m_workers.reserve(m_numThreads);
    // 创建并启动所有工作线程，每个线程执行 WorkerLoop
    for (std::size_t i = 0; i < m_numThreads; ++i) {
        m_workers.emplace_back([this] { WorkerLoop(); });
    }
}

// 析构函数：优雅关闭线程池
ThreadManager::~ThreadManager()
{
    // >>> 第一阶段：发出停止信号，唤醒所有工作线程 <<<
    {
        std::lock_guard<std::mutex> lk(m_mtx);
        m_stop.store(true, std::memory_order_relaxed); // 设置停止标志
        // 标记所有家族为 flush 状态，确保后续不再接受新任务
        for (auto& [h, fam] : m_families) {
            fam.flushReq = true;
        }
        m_cv.notify_all(); // 唤醒所有等待在 m_cv 上的 worker
    }

    // >>> 第二阶段：等待所有工作线程完全退出 <<<
    // 这是最关键的一步！必须确保所有线程退出后，才能安全清理队列
    // 否则可能出现 worker 访问已销毁的 m_queue 或 m_families
    for (auto& t : m_workers) {
        if (t.joinable()) {
            t.join(); // 阻塞等待线程结束
        }
    }

    // >>> 第三阶段：清理残留任务，调用取消回调 <<<
    // 此时已无并发，可安全操作队列和家族
    std::vector<CancelFunc> to_cancel; // 收集所有需要调用的取消回调
    {
        std::lock_guard<std::mutex> lk(m_mtx);

        // 清理主队列中残留任务
        for (auto& item : m_queue) {
            if (item.cancel)
                to_cancel.push_back(std::move(item.cancel));
        }
        m_queue.clear();

        // 清理各家族 pending 队列中残留任务
        for (auto& [h, fam] : m_families) {
            for (auto& [seq, vec] : fam.pending) {
                for (auto& item : vec) {
                    if (item.cancel)
                        to_cancel.push_back(std::move(item.cancel));
                }
            }
            fam.pending.clear();
        }
    } // 释放锁

    // 在锁外执行取消回调（避免死锁，且用户回调可能耗时）
    for (auto& cancel_func : to_cancel) {
        if (cancel_func) {
            try {
                cancel_func(); // 用户定义的清理逻辑
            } catch (...) {
                // 吞掉异常，避免析构函数抛异常（C++最佳实践）
            }
        }
    }
}

// 注册任务家族
bool ThreadManager::RegisterJobFamily(const std::string& name, Handle* outHandle, bool addInOrder, std::size_t maxOutOfOrderWindow)
{
    if (!outHandle)
        return false; // 输出句柄不能为空

    std::lock_guard<std::mutex> lk(m_mtx);
    Handle h = m_nextHandle.fetch_add(1, std::memory_order_relaxed); // 原子递增获取新句柄

    // 使用 try_emplace 避免构造临时对象，提高效率
    auto [it, inserted] = m_families.try_emplace(h);
    if (!inserted)
        return false; // 插入失败（理论上不会发生，除非句柄耗尽）

    auto& fam = it->second;
    fam.name = name;
    fam.addInOrder = addInOrder;
    fam.maxWindow = addInOrder ? maxOutOfOrderWindow : 0; // 非顺序模式下窗口无意义

    *outHandle = h;
    return true;
}

// 提交任务
bool ThreadManager::PostJob(Handle h, JobFunc&& job, std::uint64_t sequence, Priority prio, std::chrono::steady_clock::time_point deadline, CancelFunc&& onCancel)
{
    if (!job)
        return false; // 任务函数不能为空

    std::unique_lock<std::mutex> lk(m_mtx);
    auto it = m_families.find(h);
    if (it == m_families.end()) {
        // 家族不存在，立即调用取消回调（释放锁后调用，避免死锁）
        if (onCancel) {
            lk.unlock();
            try {
                onCancel();
            } catch (...) {
            }
        }
        return false;
    }
    Family& fam = it->second;

    // 本地 lambda：统一处理任务被拒绝时的逻辑（调用 onCancel + 更新统计）
    auto reject = [&](CancelFunc& cancel_func) {
        fam.canceled.fetch_add(1, std::memory_order_relaxed); // 增加取消计数
        // 注意：outstanding 不增加，因为任务未被真正接受
        if (cancel_func) {
            lk.unlock(); // 释放锁再调用用户回调（避免死锁）
            try {
                cancel_func();
            } catch (...) {
            }
        }
        return false;
    };

    // 若家族已被标记为 flush，则拒绝新任务
    if (fam.flushReq)
        return reject(onCancel);

    // 判断任务是否会立即进入主队列（用于容量检查）
    // 仅当：非顺序模式，或顺序模式下 sequence 正好是期望值
    const bool willEnterMainQueue = !fam.addInOrder || sequence == fam.nextSeq;
    if (m_queueCap > 0 && m_queue.size() >= m_queueCap && willEnterMainQueue) {
        return reject(onCancel); // 队列满，拒绝
    }

    // 顺序模式下，检查序列号是否在允许窗口内
    if (fam.addInOrder) {
        if (sequence < fam.nextSeq || (fam.maxWindow > 0 && sequence > fam.nextSeq + fam.maxWindow)) {
            return reject(onCancel); // 序列号过期或超前太多，拒绝
        }
    }

    // 任务被接受，更新统计
    fam.enqueued.fetch_add(1, std::memory_order_relaxed);
    fam.outstanding.fetch_add(1, std::memory_order_release); // 发布语义，确保 worker 看到最新值

    // 构造任务项
    QItem item { h, std::move(job), std::move(onCancel), sequence, prio, deadline };

    // 根据是否顺序模式，决定入队方式
    if (fam.addInOrder) {
        if (sequence == fam.nextSeq) {
            EnqueueUnderLock(std::move(item)); // 立即入主队列
        } else {
            fam.pending[sequence].emplace_back(std::move(item)); // 暂存到 pending
        }
    } else {
        EnqueueUnderLock(std::move(item)); // 直接入主队列
    }

    return true;
}

// 在已加锁状态下，将任务加入主队列（根据优先级决定插入位置）
void ThreadManager::EnqueueUnderLock(QItem&& it)
{
    if (it.prio == Priority::High) {
        m_queue.emplace_front(std::move(it)); // 高优先级插队到头部
    } else {
        m_queue.emplace_back(std::move(it)); // 默认优先级追加到尾部
    }
    m_cv.notify_one(); // 通知一个等待的 worker
}

// 同步等待家族任务完成
void ThreadManager::Sync(Handle h)
{
    std::unique_lock<std::mutex> lk(m_mtx);
    auto it = m_families.find(h);
    if (it == m_families.end())
        return; // 家族不存在，直接返回

    // 等待 outstanding 降为0（使用条件变量避免忙等）
    m_doneCv.wait(lk, [&] {
        return it->second.outstanding.load(std::memory_order_acquire) == 0;
    });
}

// 限时同步等待
bool ThreadManager::SyncFor(Handle h, std::chrono::milliseconds timeout)
{
    std::unique_lock<std::mutex> lk(m_mtx);
    auto it = m_families.find(h);
    if (it == m_families.end())
        return false;

    // 等待指定时间或 outstanding 降为0
    return m_doneCv.wait_for(lk, timeout, [&] {
        return it->second.outstanding.load(std::memory_order_acquire) == 0;
    });
}

// Flush 家族：取消所有未执行任务，等待执行中任务完成
bool ThreadManager::Flush(Handle h)
{
    std::vector<CancelFunc> to_cancel; // 收集取消回调
    std::unique_lock<std::mutex> lk(m_mtx);
    auto it = m_families.find(h);
    if (it == m_families.end())
        return false;

    Family& fam = it->second;
    fam.flushReq = true; // 标记为 flush 状态，后续新任务将被拒绝

    // 从主队列移除该家族所有任务
    std::deque<QItem> remaining; // 保留非该家族的任务
    for (auto& item : m_queue) {
        if (item.h == h) {
            if (item.cancel)
                to_cancel.push_back(std::move(item.cancel));
            fam.outstanding.fetch_sub(1, std::memory_order_acq_rel); // 减少进行中计数
            fam.canceled.fetch_add(1, std::memory_order_relaxed); // 增加取消计数
        } else {
            remaining.push_back(std::move(item));
        }
    }
    m_queue.swap(remaining); // 替换队列

    // 从 pending 队列移除该家族所有任务
    for (auto& [seq, vec] : fam.pending) {
        for (auto& item : vec) {
            if (item.cancel)
                to_cancel.push_back(std::move(item.cancel));
            fam.outstanding.fetch_sub(1, std::memory_order_acq_rel);
            fam.canceled.fetch_add(1, std::memory_order_relaxed);
        }
    }
    fam.pending.clear();

    // 等待所有正在执行的任务完成（此时 outstanding 只包含正在跑的任务）
    m_doneCv.wait(lk, [&] {
        return fam.outstanding.load(std::memory_order_acquire) == 0;
    });
    fam.flushReq = false; // 重置 flush 标志
    lk.unlock(); // 释放锁

    // 在锁外执行所有取消回调
    for (auto& cancel_func : to_cancel) {
        try {
            cancel_func();
        } catch (...) {
        }
    }
    return true;
}

// 设置队列容量上限
void ThreadManager::SetQueueCap(std::size_t cap)
{
    std::lock_guard<std::mutex> lk(m_mtx);
    m_queueCap = cap;
}

// 打印家族统计信息（教学用）
void ThreadManager::PrintStats(Handle h)
{
    std::lock_guard<std::mutex> lk(m_mtx);
    auto it = m_families.find(h);
    if (it == m_families.end()) {
        std::println("Family with handle {} not found.", h);
        return;
    }
    auto& fam = it->second;
    // 输出近似快照（由于原子变量，可能非精确一致）
    std::println("--- Stats for Family '{}' (H:{}) [Approximate Snapshot] ---"
                 "\n  Enqueued:   {}" // 总提交任务数
                 "\n  Outstanding:{}" // 当前进行中任务数
                 "\n  Canceled:   {}" // 被取消/拒绝任务数
                 "\n  Exceptions: {}" // 执行异常任务数
                 "\n-----------------------------------------------------",
        fam.name,
        h,
        fam.enqueued.load(),
        fam.outstanding.load(),
        fam.canceled.load(),
        fam.exceptions.load());
}

// 工作线程主循环
void ThreadManager::WorkerLoop()
{
    while (true) {
        QItem job; // 待执行任务
        Family* fam_ptr = nullptr; // 任务所属家族指针（用于更新统计）

        {
            std::unique_lock<std::mutex> lk(m_mtx);
            // 等待：直到有任务或收到停止信号
            m_cv.wait(lk,
                [&] { return m_stop.load(std::memory_order_relaxed) || !m_queue.empty(); });

            // 收到停止信号，立即退出（析构函数会清理残留任务）
            if (m_stop.load(std::memory_order_relaxed)) {
                break;
            }

            // 取出队列头部任务
            job = std::move(m_queue.front());
            m_queue.pop_front();

            // 检查家族是否存在（可能已被注销）
            auto it = m_families.find(job.h);
            if (it == m_families.end()) {
                // 家族不存在，调用取消回调（释放锁后调用）
                if (job.cancel) {
                    lk.unlock();
                    try {
                        job.cancel();
                    } catch (...) {
                    }
                }
                // 注意：无法递减 outstanding（因为 fam 不存在），这是设计上的权衡
                continue;
            }
            fam_ptr = &it->second;
        } // 释放锁 —— 任务执行阶段不持有锁，提高并发度

        // 检查任务是否已过期（deadline 已到）
        bool is_expired = job.deadline.time_since_epoch().count() != 0 && std::chrono::steady_clock::now() > job.deadline;

        // 若家族正在 flush 或任务已过期，则取消任务
        if (fam_ptr->flushReq || is_expired) {
            if (job.cancel) {
                try {
                    job.cancel(); // 调用用户取消回调
                } catch (...) {
                }
            }
            fam_ptr->canceled.fetch_add(1, std::memory_order_relaxed);
        } else {
            // 正常执行任务
            try {
                if (job.func)
                    job.func();
            } catch (...) {
                fam_ptr->exceptions.fetch_add(1, std::memory_order_relaxed); // 记录异常
            }
        }

        // 任务执行完毕，减少 outstanding 计数
        // 若减到0，通知所有等待者（Sync/Flush）
        if (fam_ptr->outstanding.fetch_sub(1, std::memory_order_acq_rel) == 1) {
            std::lock_guard<std::mutex> lk(m_mtx);
            m_doneCv.notify_all();
        }

        // 若是顺序家族，尝试调度下一个 pending 任务
        if (fam_ptr->addInOrder) {
            std::lock_guard<std::mutex> lk(m_mtx);
            // 重新查找家族（加锁后需重新验证，防止家族被删除）
            auto it = m_families.find(job.h);
            if (it != m_families.end() && job.seq == it->second.nextSeq) {
                auto& fam = it->second;
                fam.nextSeq++; // 递增期望序列号
                // 检查下一个序列号是否有 pending 任务
                auto it_pending = fam.pending.find(fam.nextSeq);
                if (it_pending != fam.pending.end()) {
                    // 有则全部入队
                    for (auto& pending_job : it_pending->second) {
                        EnqueueUnderLock(std::move(pending_job));
                    }
                    fam.pending.erase(it_pending);
                }
            }
        }
    } // end while
}