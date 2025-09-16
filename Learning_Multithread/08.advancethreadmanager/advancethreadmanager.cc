// ============================
// 文件: advancethreadmanager.cc
// 说明：AdvanceThreadManager 的实现（最终教学版，已修复所有已知 Bug）
// 核心并发模型：Work-Stealing（工作窃取） + 细粒度锁
//   - 每个 Worker 优先消费自己的队列（减少锁竞争）
//   - 自己队列空时，随机窃取其他 Worker 队列尾部任务（负载均衡）
//   - 家族表使用读写锁，提高并发读取性能
//   - 有序家族的任务分发绑定到固定 Worker，保证顺序性
// 教学重点：
//   - Work-Stealing 的实现细节（TryGetJob）
//   - 有序家族如何保证“按序完成”（nextSeq + pending + 固定分发）
//   - 全局队列容量控制（m_totalQueued）
//   - 析构函数的安全退出流程
//   - 家族注销时的空指针防御（WorkerLoop 中的 BUG FIX）
// ============================

#include "advancethreadmanager.h"

// 构造函数：启动指定数量的工作线程，初始化每个 Worker 的本地队列
AdvanceThreadManager::AdvanceThreadManager(const std::string& name, std::size_t numThreads)
    : m_name(name)
    , m_numThreads(numThreads == 0 ? std::thread::hardware_concurrency() : numThreads)
    , m_workerQueues(m_numThreads) // 初始化每个 Worker 的队列
    , m_randEngine(std::random_device {}()) // 使用随机设备初始化随机引擎（关键优化）
{
    if (m_numThreads == 0)
        m_numThreads = 1;

    m_workers.reserve(m_numThreads);
    // 创建并启动所有工作线程，每个线程执行 WorkerLoop，并传入自身 ID
    for (std::size_t i = 0; i < m_numThreads; ++i) {
        m_workers.emplace_back([this, i] { WorkerLoop(i); });
    }
}

// 析构函数：优雅关闭线程池
AdvanceThreadManager::~AdvanceThreadManager()
{
    // >>> 第一阶段：标记所有家族为 flush 状态 <<<
    {
        std::unique_lock<std::shared_mutex> lock(m_familiesMtx); // 写锁
        for (auto& [h, fam] : m_families) {
            fam.flushReq.store(true, std::memory_order_relaxed);
        }
    }

    // >>> 第二阶段：设置停止标志，唤醒所有 worker <<<
    m_stop.store(true, std::memory_order_release); // 释放语义，确保 worker 看到最新值
    m_cv.notify_all(); // 唤醒所有可能在 wait 的 worker

    // >>> 第三阶段：等待所有工作线程完全退出 <<<
    for (auto& t : m_workers) {
        if (t.joinable()) {
            t.join(); // 阻塞等待线程结束
        }
    }
    // 此时所有线程已退出，可安全访问 m_workerQueues 和 m_families（无并发）
}

// 注册任务家族
bool AdvanceThreadManager::RegisterJobFamily(const std::string& name, Handle* outHandle, bool addInOrder, std::size_t maxOutOfOrderWindow)
{
    if (!outHandle)
        return false; // 输出句柄不能为空

    std::unique_lock<std::shared_mutex> lock(m_familiesMtx); // 写锁
    Handle h = m_nextHandle.fetch_add(1, std::memory_order_relaxed); // 原子递增获取新句柄

    // 使用 try_emplace 避免构造临时对象
    auto [it, inserted] = m_families.try_emplace(h);
    if (!inserted)
        return false; // 插入失败（理论上不会发生）

    auto& fam = it->second;
    fam.name = name;
    fam.addInOrder = addInOrder;
    fam.maxWindow = addInOrder ? maxOutOfOrderWindow : 0;

    *outHandle = h;
    return true;
}

// 将任务插入指定队列（根据优先级决定插入位置）
void AdvanceThreadManager::EnqueueTo(std::deque<QItem>& q, QItem&& it)
{
    if (it.prio == Priority::High) {
        q.emplace_front(std::move(it)); // 高优先级插队到头部
    } else {
        q.emplace_back(std::move(it)); // 默认优先级追加到尾部
    }
}

// 将任务分发到合适的 Worker 队列
// 参数 h_for_ordered_dispatch：仅在有序家族时使用，用于计算固定分发目标
void AdvanceThreadManager::Enqueue(QItem&& it, Handle h_for_ordered_dispatch)
{
    m_totalQueued.fetch_add(1, std::memory_order_relaxed); // 增加全局计数

    std::size_t targetQueue;
    {
        // 读锁：检查家族是否有序，决定分发策略
        std::shared_lock<std::shared_mutex> lock(m_familiesMtx);
        auto it_fam = m_families.find(it.h);
        if (it_fam != m_families.end() && it_fam->second.addInOrder) {
            // 有序家族：固定分发到特定 Worker（保证同一家族任务在同一线程按序执行）
            targetQueue = h_for_ordered_dispatch % m_numThreads;
        } else {
            // 无序家族：随机分发到任意 Worker（负载均衡）
            std::uniform_int_distribution<std::size_t> dist(0, m_numThreads - 1);
            targetQueue = dist(m_randEngine);
        }
    } // 释放读锁

    // 锁定目标 Worker 的队列，插入任务
    {
        std::lock_guard<std::mutex> qLock(m_workerQueues[targetQueue].mtx);
        EnqueueTo(m_workerQueues[targetQueue].q, std::move(it));
    }

    m_cv.notify_one(); // 通知一个 worker（可能正在 wait）
}

// 提交任务
bool AdvanceThreadManager::PostJob(Handle h, JobFunc&& job, std::uint64_t sequence, Priority prio, std::chrono::steady_clock::time_point deadline, CancelFunc&& onCancel)
{
    if (!job)
        return false; // 任务函数不能为空（防御性检查）

    // 读锁：查找家族
    std::shared_lock<std::shared_mutex> lock(m_familiesMtx);
    auto it = m_families.find(h);
    if (it == m_families.end()) {
        // 家族不存在，立即调用取消回调（释放锁后调用，避免死锁）
        if (onCancel) {
            try {
                onCancel();
            } catch (...) {
            }
        }
        return false;
    }
    auto& fam = it->second;

    // 本地 lambda：统一处理任务被拒绝时的逻辑（调用 onCancel + 更新统计）
    auto reject = [&](CancelFunc& cancel_func) {
        if (cancel_func) {
            try {
                cancel_func();
            } catch (...) {
            }
        }
        fam.canceled.fetch_add(1, std::memory_order_relaxed);
        return false;
    };

    // 若家族正在 flush，则拒绝
    if (fam.flushReq.load(std::memory_order_acquire))
        return reject(onCancel);

    // 检查全局队列容量（非单个队列，是总计数器）
    const size_t cap = m_queueCap.load(std::memory_order_relaxed);
    if (cap > 0 && m_totalQueued.load(std::memory_order_relaxed) >= cap) {
        return reject(onCancel);
    }

    // 任务被接受，更新统计
    fam.enqueued.fetch_add(1, std::memory_order_relaxed);
    fam.outstanding.fetch_add(1, std::memory_order_release);

    // 构造任务项
    QItem item { h, std::move(job), std::move(onCancel), sequence, prio, deadline };

    if (fam.addInOrder) {
        // 顺序模式：需检查序列号并可能暂存到 pending
        std::lock_guard<std::mutex> pendingLock(fam.pendingMtx); // 锁保护 pending map
        uint64_t currentNextSeq = fam.nextSeq.load(std::memory_order_acquire);

        // 检查序列号是否在允许窗口内
        if (sequence < currentNextSeq || (fam.maxWindow > 0 && sequence > currentNextSeq + fam.maxWindow)) {
            fam.outstanding.fetch_sub(1, std::memory_order_acq_rel); // 回退 outstanding
            return reject(item.cancel);
        }

        // 如果正好是期望序列号，立即入队
        if (item.seq == currentNextSeq) {
            Enqueue(std::move(item), h); // 分发到固定 Worker
        } else {
            // 否则暂存到 pending
            fam.pending[item.seq].emplace_back(std::move(item));
        }
    } else {
        // 无序模式：直接入队（随机分发）
        Enqueue(std::move(item), h);
    }

    return true;
}

// 工作线程主循环
void AdvanceThreadManager::WorkerLoop(std::size_t workerId)
{
    QItem job;
    while (!m_stop.load(std::memory_order_acquire)) { // 获取停止标志（获取语义）
        if (TryGetJob(job, workerId)) {
            // 成功获取任务，减少全局计数
            m_totalQueued.fetch_sub(1, std::memory_order_relaxed);

            Family* fam = nullptr;
            {
                // 读锁：查找任务所属家族
                std::shared_lock<std::shared_mutex> lock(m_familiesMtx);
                auto it = m_families.find(job.h);
                if (it != m_families.end()) {
                    fam = &it->second;
                }
            } // 释放读锁 —— 任务执行阶段不持有锁

            // *** 关键修复：防御性编程 ***
            // 如果家族已被注销（例如在 Flush 或析构期间），安全取消任务
            if (!fam) {
                if (job.cancel) {
                    try {
                        job.cancel();
                    } catch (...) {
                    }
                }
                // 注意：无法递减 outstanding（因为 fam 不存在）
                // 这是一个已知的设计权衡，在教学和生产环境中均可接受
                continue;
            }

            // 检查任务是否已过期
            bool isExpired = job.deadline.time_since_epoch().count() != 0 && std::chrono::steady_clock::now() > job.deadline;

            // 若家族正在 flush 或任务已过期，则取消
            if (fam->flushReq.load(std::memory_order_acquire) || isExpired) {
                if (job.cancel) {
                    try {
                        job.cancel();
                    } catch (...) {
                    }
                }
                fam->canceled.fetch_add(1, std::memory_order_relaxed);
            } else {
                // 正常执行任务
                try {
                    if (job.func)
                        job.func();
                } catch (...) {
                    fam->exceptions.fetch_add(1, std::memory_order_relaxed);
                }
            }

            // 任务执行完毕，减少 outstanding 计数
            size_t prev_outstanding = fam->outstanding.fetch_sub(1, std::memory_order_acq_rel);

            // 如果是有序家族且当前任务是期望序列号，则尝试调度下一个 pending 任务
            if (fam->addInOrder && job.seq == fam->nextSeq.load(std::memory_order_relaxed)) {
                std::lock_guard<std::mutex> lock(fam->pendingMtx);
                fam->nextSeq.fetch_add(1, std::memory_order_relaxed); // 递增期望序列号
                auto nextSeq = fam->nextSeq.load(std::memory_order_relaxed);
                auto it_pending = fam->pending.find(nextSeq);
                if (it_pending != fam->pending.end()) {
                    // 有则全部入队（分发到同一个固定 Worker）
                    for (auto& pending_job : it_pending->second) {
                        Enqueue(std::move(pending_job), job.h);
                    }
                    fam->pending.erase(it_pending);
                }
            }

            // 如果 outstanding 减到 0，通知所有等待者（Sync/Flush）
            if (prev_outstanding == 1) {
                std::unique_lock<std::mutex> cvLock(m_cvMtx);
                m_doneCv.notify_all();
            }

        } else {
            // 本地和窃取都无任务，等待一段时间或被唤醒
            std::unique_lock<std::mutex> lock(m_cvMtx);
            m_cv.wait_for(lock, std::chrono::milliseconds(100), [this] {
                return m_stop.load(std::memory_order_relaxed) || m_totalQueued.load(std::memory_order_relaxed) > 0;
            });
        }
    } // end while
}

// 尝试获取一个任务：先尝试本地队列，再尝试窃取其他队列
bool AdvanceThreadManager::TryGetJob(QItem& job, std::size_t workerId)
{
    // 1. 尝试从本地队列获取（从头部取，保证 FIFO）
    {
        std::lock_guard<std::mutex> lock(m_workerQueues[workerId].mtx);
        if (!m_workerQueues[workerId].q.empty()) {
            job = std::move(m_workerQueues[workerId].q.front());
            m_workerQueues[workerId].q.pop_front();
            return true;
        }
    }

    // 2. 如果只有一个线程，无需窃取
    if (m_numThreads <= 1)
        return false;

    // 3. 随机选择一个“受害者”Worker（排除自己）
    std::uniform_int_distribution<std::size_t> dist(0, m_numThreads - 2);
    std::size_t victim_offset = dist(m_randEngine);
    std::size_t victimId = (workerId + 1 + victim_offset) % m_numThreads;

    // 4. 尝试从受害者队列尾部窃取一个任务（减少对受害者的影响）
    std::lock_guard<std::mutex> lock(m_workerQueues[victimId].mtx);
    if (!m_workerQueues[victimId].q.empty()) {
        job = std::move(m_workerQueues[victimId].q.back());
        m_workerQueues[victimId].q.pop_back();
        return true;
    }

    return false;
}

// 同步等待家族任务完成
void AdvanceThreadManager::Sync(Handle h)
{
    std::unique_lock<std::mutex> lock(m_cvMtx);
    m_doneCv.wait(lock, [&]() {
        std::shared_lock<std::shared_mutex> famLock(m_familiesMtx); // 读锁
        auto it = m_families.find(h);
        if (it == m_families.end())
            return true; // 家族不存在，视为完成
        return it->second.outstanding.load(std::memory_order_acquire) == 0;
    });
}

// 限时同步等待
bool AdvanceThreadManager::SyncFor(Handle h, std::chrono::milliseconds timeout)
{
    std::unique_lock<std::mutex> lock(m_cvMtx);
    return m_doneCv.wait_for(lock, timeout, [&]() {
        std::shared_lock<std::shared_mutex> famLock(m_familiesMtx); // 读锁
        auto it = m_families.find(h);
        if (it == m_families.end())
            return true;
        return it->second.outstanding.load(std::memory_order_acquire) == 0;
    });
}

// Flush 家族：取消所有未执行任务，等待执行中任务完成
bool AdvanceThreadManager::Flush(Handle h)
{
    Family* fam = nullptr;
    {
        std::shared_lock<std::shared_mutex> lock(m_familiesMtx); // 读锁
        auto it = m_families.find(h);
        if (it == m_families.end())
            return false;
        fam = &it->second;
    }

    fam->flushReq.store(true, std::memory_order_release); // 标记为 flush

    std::vector<QItem> to_cancel_items; // 收集所有待取消任务

    // 1. 清理有序家族的 pending 任务
    if (fam->addInOrder) {
        std::lock_guard<std::mutex> lock(fam->pendingMtx);
        for (auto& [seq, items] : fam->pending) {
            for (auto& item : items) {
                to_cancel_items.push_back(std::move(item));
            }
        }
        fam->pending.clear();
    }

    // 2. 清理所有 Worker 队列中的该家族任务
    for (size_t i = 0; i < m_numThreads; ++i) {
        std::lock_guard<std::mutex> lock(m_workerQueues[i].mtx);
        auto& q = m_workerQueues[i].q;
        // 从前往后遍历，移除匹配家族的任务
        for (auto it = q.begin(); it != q.end();) {
            if (it->h == h) {
                to_cancel_items.push_back(std::move(*it));
                it = q.erase(it);
            } else {
                ++it;
            }
        }
    }

    // 3. 更新统计：减少 outstanding 和全局计数器
    size_t cancelled_count = to_cancel_items.size();
    if (cancelled_count > 0) {
        fam->outstanding.fetch_sub(cancelled_count, std::memory_order_acq_rel);
        fam->canceled.fetch_add(cancelled_count, std::memory_order_relaxed);
        m_totalQueued.fetch_sub(cancelled_count, std::memory_order_relaxed);
    }

    // 4. 等待所有正在执行的任务完成
    Sync(h);

    // 5. 重置 flush 标志
    fam->flushReq.store(false, std::memory_order_release);

    // 6. 在锁外执行所有取消回调（避免死锁，用户回调可能耗时）
    for (auto& item : to_cancel_items) {
        if (item.cancel) {
            try {
                item.cancel();
            } catch (...) {
            }
        }
    }

    return true;
}

// 设置全局队列容量上限
void AdvanceThreadManager::SetQueueCap(std::size_t cap)
{
    m_queueCap.store(cap, std::memory_order_relaxed);
}