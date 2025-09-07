// ============================
// file: threadmanager.cpp
// 说明：对应 threadmanager.h 的实现。严格保持代码逻辑不变，仅重写注释。
// ============================

#include "threadmanager.h"
#include "ftrace.h"
#include <cassert>

// `Create` 方法：静态方法，用于创建 `ThreadManager` 实例并进行初始化
bool ThreadManager::Create(ThreadManager** ppInstance, const std::string& name, std::size_t numThreads)
{
    bool ret = true;

    // 检查输入参数
    if (ppInstance == nullptr) {
        ret = false;
        return ret;
    }

    Ftrace::ftrace_duration_begin("ThreadManager::Create " + name);

    // 创建 ThreadManager 实例
    *ppInstance = new ThreadManager(numThreads);
    if (nullptr != *ppInstance) {
        // 调用 Initialize 进行进一步初始化
        ret = (*ppInstance)->Initialize(name);
    }

    Ftrace::ftrace_duration_end();
    return ret;
}

void ThreadManager::Destroy()
{
    delete this;
}

// `Initialize` 方法：用于设置线程池名称等初始化操作
bool ThreadManager::Initialize(const std::string& name)
{
    m_name = name; // 设置线程池名称

    // 至少创建 1 个 worker
    if (m_numThreads == 0)
        m_numThreads = 1;
    m_workers.reserve(m_numThreads);
    for (std::size_t i = 0; i < m_numThreads; ++i) {
        m_workers.emplace_back([this] { WorkerLoop(); });
    }

    return true; // 如果初始化成功，返回 true
}

ThreadManager::ThreadManager(std::size_t threadCount)
    : m_numThreads(threadCount)
    , m_stop(false)
    , m_nextHandle(1)
{
}

ThreadManager::~ThreadManager()
{
    // 析构做“软 Flush”：
    // 1) 全部家族标记 flushReq=true，拒绝新任务
    // 2) 将全局队列与各家族 pending 中未执行任务收集到 to_cancel
    // 3) 回收 outstanding 与统计 canceled
    // 4) 通知 worker 退出（m_stop=true 且队列清空后）
    // 5) 线程 join
    // 6) 在锁外逐个执行 cancel 回调，避免回调内部再抢锁造成死锁

    struct ToCancel {
        CancelFunc cancel;
        void* data;
    };
    std::vector<ToCancel> to_cancel;

    {
        std::lock_guard<std::mutex> lk(m_mtx);

        // 所有家族进入 Flush 阶段
        for (auto& [h, fam] : m_families)
            fam.flushReq = true;

        // 剔除全局队列：统计并移入 to_cancel
        std::deque<QItem> rest;
        rest.swap(m_queue);
        for (auto& q : rest) {
            auto it = m_families.find(q.h);
            if (it != m_families.end()) {
                Family& fam = it->second;
                to_cancel.push_back({ fam.cancel, q.data });
                fam.outstanding.fetch_sub(1, std::memory_order_acq_rel);
                fam.canceled.fetch_add(1, std::memory_order_relaxed);
            }
        }

        // 清空各家族 pending：统计并移入 to_cancel
        for (auto& [h, fam] : m_families) {
            std::size_t removed = 0;
            for (auto& [seq, vec] : fam.pending) {
                for (auto& qi : vec) {
                    to_cancel.push_back({ fam.cancel, qi.data });
                    ++removed;
                }
            }
            fam.pending.clear();
            if (removed) {
                fam.outstanding.fetch_sub(removed, std::memory_order_acq_rel);
                fam.canceled.fetch_add(removed, std::memory_order_relaxed);
            }
        }

        // 唤醒可能等待 Sync/Flush 的线程（有家族的 outstanding 可能已归零）
        m_doneCv.notify_all();

        // 标记停止：worker 在队列耗尽后退出
        m_stop.store(true, std::memory_order_relaxed);
    }
    m_cv.notify_all();

    // 回收 worker
    for (auto& t : m_workers)
        if (t.joinable())
            t.join();

    // 取消回调在锁外执行，避免回调拿锁导致潜在死锁
    for (auto& c : to_cancel) {
        if (c.cancel) {
            try {
                c.cancel(c.data);
            } catch (...) {
            }
        }
    }
}

bool ThreadManager::RegisterJobFamily(const JobFunc& fn,
    const std::string& name,
    Handle* outHandle,
    bool addInOrder,
    std::size_t maxOutOfOrderWindow,
    CancelFunc cancel)
{
    // 基本校验：必须有输出句柄且执行函数有效
    if (!outHandle || !fn)
        return false;
    std::lock_guard<std::mutex> lk(m_mtx);

    // 分配新的家族句柄并初始化元数据
    Handle h = m_nextHandle++;
    auto [it, inserted] = m_families.try_emplace(h);
    (void)inserted;
    Family& fam = it->second;
    fam.func = fn;
    fam.cancel = cancel;
    fam.name = name;
    fam.addInOrder = addInOrder;
    fam.maxWindow = addInOrder ? maxOutOfOrderWindow : 0;
    fam.nextSeq = 0;

    *outHandle = h;
    return true;
}

bool ThreadManager::PostJob(Handle h,
    void* userData,
    std::uint64_t sequence,
    Priority prio,
    std::chrono::steady_clock::time_point deadline)
{
    // 进入临界区：定位家族并进行状态/窗口/上限检查
    std::unique_lock<std::mutex> lk(m_mtx);
    auto it = m_families.find(h);
    if (it == m_families.end())
        return false;
    Family& fam = it->second;

    // 统计累计提交
    fam.enqueued.fetch_add(1, std::memory_order_relaxed);

    // 本地工具：拒绝并在锁外执行取消回调
    auto reject_and_maybe_cancel = [&](void* p) {
        fam.canceled.fetch_add(1, std::memory_order_relaxed);
        CancelFunc cancel = fam.cancel;
        lk.unlock(); // cancel 必须在锁外执行
        if (cancel && p) {
            try {
                cancel(p);
            } catch (...) {
            }
        }
        return false;
    };

    // Flush 阶段拒绝进入
    if (fam.flushReq)
        return reject_and_maybe_cancel(userData);

    // 有序家族：过旧序号或越过“未来窗口”的序号拒绝（避免污染 pending）
    if (fam.addInOrder && sequence < fam.nextSeq) {
        return reject_and_maybe_cancel(userData);
    }
    if (fam.addInOrder && fam.maxWindow && sequence > fam.nextSeq && (sequence - fam.nextSeq) > fam.maxWindow) {
        return reject_and_maybe_cancel(userData);
    }

    // 通过基本检查，计入在途
    fam.outstanding.fetch_add(1, std::memory_order_release);

    QItem item { h, fam.func, userData, sequence, prio, deadline };

    if (fam.addInOrder) {
        if (sequence == fam.nextSeq) {
            // 立即可执行：检查全局队列上限
            if (m_queueCap && m_queue.size() >= m_queueCap) {
                fam.outstanding.fetch_sub(1, std::memory_order_acq_rel);
                return reject_and_maybe_cancel(userData);
            }
            EnqueueNoLock(std::move(item));
        } else {
            // 未来序号：放入 pending（pending 不受队列上限限制）
            fam.pending[sequence].emplace_back(std::move(item));
        }
    } else {
        // 无序家族：仅受全局队列上限限制
        if (m_queueCap && m_queue.size() >= m_queueCap) {
            fam.outstanding.fetch_sub(1, std::memory_order_acq_rel);
            return reject_and_maybe_cancel(userData);
        }
        EnqueueNoLock(std::move(item));
    }
    return true;
}

void ThreadManager::EnqueueNoLock(QItem&& it)
{
    // 要求：调用方已持有 m_mtx
    // 行为：根据优先级决定插入队列头/尾，并唤醒一个 worker
    if (it.prio == Priority::High)
        m_queue.emplace_front(std::move(it));
    else
        m_queue.emplace_back(std::move(it));
    m_cv.notify_one();
}

void ThreadManager::Sync(Handle h)
{
    // 等待指定家族的 outstanding 归零
    std::unique_lock<std::mutex> lk(m_mtx);
    auto it = m_families.find(h);
    if (it == m_families.end())
        return;
    Family& fam = it->second;
    m_doneCv.wait(lk, [&] {
        return fam.outstanding.load(std::memory_order_acquire) == 0;
    });
}

bool ThreadManager::SyncFor(Handle h, std::chrono::milliseconds timeout)
{
    // 限时等待 outstanding 归零
    std::unique_lock<std::mutex> lk(m_mtx);
    auto it = m_families.find(h);
    if (it == m_families.end())
        return false;
    Family& fam = it->second;
    return m_doneCv.wait_for(lk, timeout, [&] {
        return fam.outstanding.load(std::memory_order_acquire) == 0;
    });
}

bool ThreadManager::Flush(Handle h)
{
    // 流程：
    // 1) 标记家族 flushReq=true，复制 cancel 回调
    // 2) 从全局队列剔除该家族任务 → 计数与收集 to_cancel
    // 3) 清空 pending → 计数与收集 to_cancel
    // 4) 等待 outstanding 归零 → 解锁
    // 5) 在锁外逐个调用 cancel
    CancelFunc cancel_copy;
    std::vector<void*> to_cancel;

    std::unique_lock<std::mutex> lk(m_mtx);
    auto it = m_families.find(h);
    if (it == m_families.end())
        return false;
    Family& fam = it->second;

    fam.flushReq = true; // 拒绝新任务
    cancel_copy = fam.cancel; // 复制回调（出锁调用）

    // 剔除全局队列中属于该家族的任务
    std::size_t removed = 0;
    {
        std::deque<QItem> rest;
        rest.swap(m_queue);
        for (auto& q : rest) {
            if (q.h == h) {
                to_cancel.push_back(q.data);
                ++removed;
            } else {
                m_queue.push_back(std::move(q));
            }
        }
    }

    // 清空 pending
    for (auto& [seq, vec] : fam.pending) {
        for (auto& qi : vec) {
            to_cancel.push_back(qi.data);
            ++removed;
        }
    }
    fam.pending.clear();

    // 回收 outstanding，可能直接满足等待条件
    if (removed > 0) {
        fam.outstanding.fetch_sub(removed, std::memory_order_acq_rel);
        m_doneCv.notify_all();
    }

    // 等待仅剩“执行中”的任务跑完
    m_doneCv.wait(lk, [&] {
        return fam.outstanding.load(std::memory_order_acquire) == 0;
    });
    fam.flushReq = false;
    lk.unlock();

    // 锁外取消
    if (cancel_copy) {
        for (void* p : to_cancel) {
            try {
                cancel_copy(p);
            } catch (...) {
            }
        }
    }
    fam.canceled.fetch_add(to_cancel.size(), std::memory_order_relaxed);
    return true;
}

void ThreadManager::WorkerLoop()
{
    // 不断从全局队列取任务并处理：
    // - Flush 状态：直接取消
    // - 有序家族：
    //     seq == nextSeq  → 执行
    //     seq  > nextSeq  → 放入 pending 并继续取下一条（避免阻塞队列头）
    //     seq  < nextSeq  → 标记为“旧序号”，准备直接取消
    // - 无序家族：直接执行
    // 执行后若为有序家族，推进 nextSeq 并释放连续 pending
    while (true) {
        QItem job {};
        Family* famPtr = nullptr;
        bool cancelForOldSeq = false; // 标记“旧序号”导致的取消

        {
            std::unique_lock<std::mutex> lk(m_mtx);
            m_cv.wait(lk, [&] { return m_stop.load(std::memory_order_relaxed) || !m_queue.empty(); });
            if (m_stop.load(std::memory_order_relaxed) && m_queue.empty())
                break;

            // 取任务；遇到未来序号则转存 pending 并继续取下一条，避免队列被卡住
            while (true) {
                if (m_queue.empty()) {
                    job = {};
                    break;
                }
                job = std::move(m_queue.front());
                m_queue.pop_front();

                auto it = m_families.find(job.h);
                if (it == m_families.end()) {
                    // 不存在的家族（理论上不发生）：丢弃后继续
                    job.data = nullptr;
                    continue;
                }
                Family& fam = it->second;
                famPtr = &fam;

                if (fam.flushReq) {
                    // Flush 中：离开锁后做取消
                    break;
                }
                if (fam.addInOrder) {
                    if (job.seq == fam.nextSeq) {
                        break; // 正好是期望序号，可执行
                    } else if (job.seq > fam.nextSeq) {
                        // 未来序号：入 pending，继续从队列取下一条
                        fam.pending[job.seq].emplace_back(std::move(job));
                        continue;
                    } else {
                        // 旧序号：标记为“需要取消”，离开锁后执行取消
                        cancelForOldSeq = true;
                        break;
                    }
                } else {
                    break; // 无序家族：直接执行
                }
            }
        }

        if (!famPtr)
            continue; // 容错

        // 在锁外复制回调，以便安全执行
        CancelFunc cancelCopy = famPtr->cancel;
        JobFunc funcCopy = famPtr->func;

        // Flush / 旧序号 / deadline 判定（在锁外做尽量少的加锁）
        bool needCancel = false;
        {
            std::lock_guard<std::mutex> lk(m_mtx);
            auto it = m_families.find(job.h);
            if (it == m_families.end())
                needCancel = true;
            else if (it->second.flushReq)
                needCancel = true;
        }
        if (cancelForOldSeq)
            needCancel = true;

        const bool hasDeadline = (job.deadline.time_since_epoch().count() != 0);
        if (!needCancel && hasDeadline && std::chrono::steady_clock::now() > job.deadline) {
            // 已过期：取消
            needCancel = true;
        }

        if (needCancel) {
            if (cancelCopy && job.data) {
                try {
                    cancelCopy(job.data);
                } catch (...) {
                }
            }
            // outstanding 归零时唤醒等待者
            if (famPtr->outstanding.fetch_sub(1, std::memory_order_acq_rel) == 1) {
                m_doneCv.notify_all();
            }
            famPtr->canceled.fetch_add(1, std::memory_order_relaxed);
            continue;
        }

        // 执行阶段（锁外执行，避免阻塞其他线程）
        bool hadException = false;
        try {
            funcCopy(job.data);
        } catch (...) {
            hadException = true;
        }
        if (hadException) {
            famPtr->exceptions.fetch_add(1, std::memory_order_relaxed);
        }
        if (famPtr->outstanding.fetch_sub(1, std::memory_order_acq_rel) == 1) {
            m_doneCv.notify_all();
        }

        // 有序家族：推进 nextSeq，并批量释放连续 pending
        if (famPtr->addInOrder) {
            std::unique_lock<std::mutex> lk(m_mtx);
            auto it = m_families.find(job.h);
            if (it != m_families.end()) {
                Family& fam = it->second;
                if (job.seq == fam.nextSeq) {
                    ++fam.nextSeq;
                    // 只要存在“下一个连续序号”的 pending，就回放到全局队列
                    while (true) {
                        auto itVec = fam.pending.find(fam.nextSeq);
                        if (itVec == fam.pending.end() || itVec->second.empty())
                            break;
                        auto vec = std::move(itVec->second);
                        fam.pending.erase(itVec);
                        for (auto& qi : vec) {
                            m_queue.emplace_back(std::move(qi));
                        }
                        m_cv.notify_all();
                        ++fam.nextSeq;
                    }
                }
            }
        }
    }
}