// ============================
// file: threadmanager.cc
// ============================
#include "threadmanager.h"
#include <cassert>

ThreadManager::ThreadManager(std::size_t threadCount)
    : m_stop(false)
    , m_nextHandle(1)
{
    if (threadCount == 0)
        threadCount = 1;
    m_workers.reserve(threadCount);
    for (std::size_t i = 0; i < threadCount; ++i) {
        m_workers.emplace_back([this] { workerLoop(); });
    }
}

ThreadManager::~ThreadManager()
{
    // 停止并回收线程：不抢占，跑完队列
    {
        std::lock_guard<std::mutex> lk(m_mtx);
        m_stop.store(true, std::memory_order_relaxed);
    }
    m_cv.notify_all();
    for (auto& t : m_workers)
        if (t.joinable())
            t.join();
}

bool ThreadManager::RegisterJobFamily(const JobFunc& fn,
    const std::string& name,
    Handle* outHandle,
    bool addInOrder,
    std::size_t maxOutOfOrderWindow,
    CancelFunc cancel)
{
    if (!outHandle || !fn)
        return false;
    std::lock_guard<std::mutex> lk(m_mtx);

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
    std::unique_lock<std::mutex> lk(m_mtx);
    auto it = m_families.find(h);
    if (it == m_families.end())
        return false;
    Family& fam = it->second;

    if (fam.flushReq)
        return false; // Flush 期间拒绝新任务

    QItem item { h, fam.func, userData, sequence, prio, deadline };
    fam.enqueued.fetch_add(1, std::memory_order_relaxed);

    // 有序家族：过期序号直接拒绝（不污染 pending）
    if (fam.addInOrder && sequence < fam.nextSeq) {
        fam.canceled.fetch_add(1, std::memory_order_relaxed);
        return false; // 提交方需自行释放 userData
    }
    // 有序家族：乱序窗口限制（防止 pending 无限增长）
    if (fam.addInOrder && fam.maxWindow && sequence > fam.nextSeq && (sequence - fam.nextSeq) > fam.maxWindow) {
        fam.canceled.fetch_add(1, std::memory_order_relaxed);
        return false; // 提交方需自行释放 userData
    }

    // 计入在途
    fam.outstanding.fetch_add(1, std::memory_order_release);

    if (fam.addInOrder) {
        if (sequence == fam.nextSeq) {
            enqueueNoLock(std::move(item));
        } else { // sequence > nextSeq
            fam.pending[sequence].emplace_back(std::move(item));
        }
    } else {
        enqueueNoLock(std::move(item));
    }
    return true;
}

void ThreadManager::enqueueNoLock(QItem&& it)
{
    // 需要在持有 m_mtx 的情况下调用；仅做 push + notify。
    m_queue.emplace_back(std::move(it));
    m_cv.notify_one();
}

void ThreadManager::Sync(Handle h)
{
    std::unique_lock<std::mutex> lk(m_mtx);
    auto it = m_families.find(h);
    if (it == m_families.end())
        return; // 不存在直接返回
    Family& fam = it->second;
    m_doneCv.wait(lk, [&] { return fam.outstanding.load(std::memory_order_acquire) == 0; });
}

bool ThreadManager::SyncFor(Handle h, std::chrono::milliseconds timeout)
{
    std::unique_lock<std::mutex> lk(m_mtx);
    auto it = m_families.find(h);
    if (it == m_families.end())
        return false;
    Family& fam = it->second;
    return m_doneCv.wait_for(lk, timeout, [&] { return fam.outstanding.load(std::memory_order_acquire) == 0; });
}

bool ThreadManager::Flush(Handle h)
{
    CancelFunc cancel_copy;
    std::vector<void*> to_cancel;

    std::unique_lock<std::mutex> lk(m_mtx);
    auto it = m_families.find(h);
    if (it == m_families.end())
        return false;
    Family& fam = it->second;

    fam.flushReq = true; // 1) 拒绝新任务
    cancel_copy = fam.cancel; //    复制回调，出锁调用

    // 2) 从全局队列剔除该家族的任务
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

    // 3) 把 pending 全部移出
    for (auto& [seq, vec] : fam.pending) {
        for (auto& qi : vec) {
            to_cancel.push_back(qi.data);
            ++removed;
        }
    }
    fam.pending.clear();

    // 4) 为被剔除/移出的任务回收 outstanding
    if (removed > 0) {
        fam.outstanding.fetch_sub(removed, std::memory_order_acq_rel);
        m_doneCv.notify_all(); // 可能立刻满足等待条件
    }

    // 5) 等待“仅剩运行中”的任务全部结束
    m_doneCv.wait(lk, [&] { return fam.outstanding.load(std::memory_order_acquire) == 0; });
    fam.flushReq = false;
    lk.unlock();

    // 6) 在无锁环境下调用 cancel
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

void ThreadManager::workerLoop()
{
    while (true) {
        QItem job {};
        Family* famPtr = nullptr; // 用于计数/推进；不跨 Unregister（本实现不支持 Unregister）

        {
            std::unique_lock<std::mutex> lk(m_mtx);
            m_cv.wait(lk, [&] { return m_stop.load(std::memory_order_relaxed) || !m_queue.empty(); });
            if (m_stop.load(std::memory_order_relaxed) && m_queue.empty())
                break;

            // 取一个任务；若遇到“未到序”的任务，转入 pending 并继续取下一条，避免队列头阻塞
            while (true) {
                if (m_queue.empty()) {
                    job = {};
                    break;
                }
                job = std::move(m_queue.front());
                m_queue.pop_front();

                auto it = m_families.find(job.h);
                if (it == m_families.end()) {
                    // 理论上不会发生（不支持 Unregister）。丢弃并继续。
                    job.data = nullptr; // 无法安全释放
                    continue;
                }
                Family& fam = it->second;
                famPtr = &fam;

                if (fam.flushReq) {
                    // Flush 中：当场取消（锁外调用 cancel），但先把 job 留在 job 里
                    break;
                }
                if (fam.addInOrder) {
                    if (job.seq == fam.nextSeq) {
                        break; // 可执行
                    } else if (job.seq > fam.nextSeq) {
                        fam.pending[job.seq].emplace_back(std::move(job));
                        continue; // 继续从队列取下一条
                    } else { // job.seq < nextSeq
                        // 旧序号：当场取消
                        break;
                    }
                } else {
                    break; // 无序：可执行
                }
            }
        }

        if (!famPtr)
            continue; // 保险

        // 复制回调，锁外执行
        CancelFunc cancelCopy = famPtr->cancel;
        JobFunc funcCopy = famPtr->func;

        // Flush 或旧序号（<nextSeq）视为取消
        bool needCancel = false;
        {
            std::lock_guard<std::mutex> lk(m_mtx);
            auto it = m_families.find(job.h);
            if (it == m_families.end())
                needCancel = true;
            else if (it->second.flushReq)
                needCancel = true;
        }

        // 过期判定（deadline 非零 且 已经过期）
        const bool hasDeadline = (job.deadline.time_since_epoch().count() != 0);
        if (!needCancel && hasDeadline && std::chrono::steady_clock::now() > job.deadline) {
            needCancel = true;
        }

        if (needCancel) {
            if (cancelCopy && job.data) {
                try {
                    cancelCopy(job.data);
                } catch (...) {
                }
            }
            if (famPtr->outstanding.fetch_sub(1, std::memory_order_acq_rel) == 1) {
                std::lock_guard<std::mutex> lk(m_mtx);
                m_doneCv.notify_all();
            }
            famPtr->canceled.fetch_add(1, std::memory_order_relaxed);
            continue;
        }

        // 执行
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
            std::lock_guard<std::mutex> lk(m_mtx);
            m_doneCv.notify_all();
        }

        // 有序家族：推进 nextSeq，并顺延放行 pending[nextSeq]
        if (famPtr->addInOrder) {
            std::unique_lock<std::mutex> lk(m_mtx);
            auto it = m_families.find(job.h);
            if (it != m_families.end()) {
                Family& fam = it->second;
                if (job.seq == fam.nextSeq) {
                    ++fam.nextSeq;
                    // 把当前可执行序号的 pending 放回全局队列（全部）
                    while (true) {
                        auto itVec = fam.pending.find(fam.nextSeq);
                        if (itVec == fam.pending.end() || itVec->second.empty())
                            break;
                        auto vec = std::move(itVec->second);
                        fam.pending.erase(itVec);
                        // 持锁直接回填队列
                        for (auto& qi : vec) {
                            m_queue.emplace_back(std::move(qi));
                        }
                        m_cv.notify_all();
                    }
                }
            }
        }
    }
}