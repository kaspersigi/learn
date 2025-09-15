// ============================
// file: threadmanager.cc
// 说明：ThreadManager 的实现 (最终教学版)
// 核心并发逻辑与原版 threadmanager 保持不变，仅适配新的 API 并采纳专家建议进行微调。
// ============================
#include "threadmanager.h"
#include <print>

ThreadManager::ThreadManager(const std::string& name, std::size_t numThreads)
    : m_name(name)
    , m_numThreads(numThreads == 0 ? 1 : numThreads)
{
    if (m_numThreads == 0)
        m_numThreads = 1;
    m_workers.reserve(m_numThreads);
    for (std::size_t i = 0; i < m_numThreads; ++i) {
        m_workers.emplace_back([this] { WorkerLoop(); });
    }
}

ThreadManager::~ThreadManager()
{
    // [关键修复] 修复析构函数中的竞态条件
    // 1. 发出停止信号，唤醒所有 worker 准备退出
    {
        std::lock_guard<std::mutex> lk(m_mtx);
        m_stop.store(true, std::memory_order_relaxed);
        for (auto& [h, fam] : m_families) {
            fam.flushReq = true; // 确保所有任务都被视为 "flushed"
        }
        m_cv.notify_all();
    }

    // 2. 等待所有 worker 线程完全退出
    // [教学提示] 这是最关键的一步，必须在清理队列前完成，
    // 确保在清理队列时，没有任何线程会再访问它们。
    for (auto& t : m_workers) {
        if (t.joinable()) {
            t.join();
        }
    }

    // 3. 安全地清理剩余任务，此时已无并发
    std::vector<CancelFunc> to_cancel;
    {
        std::lock_guard<std::mutex> lk(m_mtx);
        for (auto& item : m_queue) {
            if (item.cancel)
                to_cancel.push_back(std::move(item.cancel));
        }
        m_queue.clear();

        for (auto& [h, fam] : m_families) {
            for (auto& [seq, vec] : fam.pending) {
                for (auto& item : vec) {
                    if (item.cancel)
                        to_cancel.push_back(std::move(item.cancel));
                }
            }
            fam.pending.clear();
        }
    }

    // 4. 在所有锁之外执行取消回调
    for (auto& cancel_func : to_cancel) {
        if (cancel_func) {
            try {
                cancel_func();
            } catch (...) {
            }
        }
    }
}

bool ThreadManager::RegisterJobFamily(const std::string& name, Handle* outHandle, bool addInOrder, std::size_t maxOutOfOrderWindow)
{
    if (!outHandle)
        return false;

    std::lock_guard<std::mutex> lk(m_mtx);
    Handle h = m_nextHandle.fetch_add(1, std::memory_order_relaxed);

    // 使用 try_emplace 避免移动/拷贝不可移动的 Family 结构体
    auto [it, inserted] = m_families.try_emplace(h);
    if (!inserted)
        return false;

    auto& fam = it->second;
    fam.name = name;
    fam.addInOrder = addInOrder;
    fam.maxWindow = addInOrder ? maxOutOfOrderWindow : 0;

    *outHandle = h;
    return true;
}

bool ThreadManager::PostJob(Handle h, JobFunc&& job, std::uint64_t sequence, Priority prio, std::chrono::steady_clock::time_point deadline, CancelFunc&& onCancel)
{
    if (!job)
        return false;

    std::unique_lock<std::mutex> lk(m_mtx);
    auto it = m_families.find(h);
    if (it == m_families.end()) {
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

    // 本地 lambda 用于统一处理拒绝任务的逻辑
    auto reject = [&](CancelFunc& cancel_func) {
        fam.canceled.fetch_add(1, std::memory_order_relaxed);
        // 注意：outstanding 计数在此处不增不减，因为任务从未被成功接纳
        if (cancel_func) {
            lk.unlock();
            try {
                cancel_func();
            } catch (...) {
            }
        }
        return false;
    };

    if (fam.flushReq)
        return reject(onCancel);

    // [可读性优化] 仅当任务能立即进入主队列时才受容量限制
    const bool willEnterMainQueue = !fam.addInOrder || sequence == fam.nextSeq;
    if (m_queueCap > 0 && m_queue.size() >= m_queueCap && willEnterMainQueue) {
        return reject(onCancel);
    }

    if (fam.addInOrder) {
        // [教学提示] 若启用有序模式，sequence 应单调递增
        // 重复或过时的 sequence 将被拒绝
        if (sequence < fam.nextSeq || (fam.maxWindow > 0 && sequence > fam.nextSeq + fam.maxWindow)) {
            return reject(onCancel);
        }
    }

    fam.enqueued.fetch_add(1, std::memory_order_relaxed);
    fam.outstanding.fetch_add(1, std::memory_order_release);

    QItem item { h, std::move(job), std::move(onCancel), sequence, prio, deadline };

    if (fam.addInOrder) {
        if (sequence == fam.nextSeq) {
            EnqueueUnderLock(std::move(item));
        } else {
            fam.pending[sequence].emplace_back(std::move(item));
        }
    } else {
        EnqueueUnderLock(std::move(item));
    }

    return true;
}

void ThreadManager::EnqueueUnderLock(QItem&& it)
{
    if (it.prio == Priority::High) {
        m_queue.emplace_front(std::move(it));
    } else {
        m_queue.emplace_back(std::move(it));
    }
    m_cv.notify_one();
}

void ThreadManager::Sync(Handle h)
{
    std::unique_lock<std::mutex> lk(m_mtx);
    auto it = m_families.find(h);
    if (it == m_families.end())
        return;
    m_doneCv.wait(lk, [&] {
        return it->second.outstanding.load(std::memory_order_acquire) == 0;
    });
}

bool ThreadManager::SyncFor(Handle h, std::chrono::milliseconds timeout)
{
    std::unique_lock<std::mutex> lk(m_mtx);
    auto it = m_families.find(h);
    if (it == m_families.end())
        return false;
    return m_doneCv.wait_for(lk, timeout, [&] {
        return it->second.outstanding.load(std::memory_order_acquire) == 0;
    });
}

bool ThreadManager::Flush(Handle h)
{
    std::vector<CancelFunc> to_cancel;
    std::unique_lock<std::mutex> lk(m_mtx);
    auto it = m_families.find(h);
    if (it == m_families.end())
        return false;
    Family& fam = it->second;

    fam.flushReq = true;

    // 从主队列移除
    std::deque<QItem> remaining;
    for (auto& item : m_queue) {
        if (item.h == h) {
            if (item.cancel)
                to_cancel.push_back(std::move(item.cancel));
            fam.outstanding.fetch_sub(1, std::memory_order_acq_rel);
            fam.canceled.fetch_add(1, std::memory_order_relaxed);
        } else {
            remaining.push_back(std::move(item));
        }
    }
    m_queue.swap(remaining);

    // 从 pending 列表移除
    for (auto& [seq, vec] : fam.pending) {
        for (auto& item : vec) {
            if (item.cancel)
                to_cancel.push_back(std::move(item.cancel));
            fam.outstanding.fetch_sub(1, std::memory_order_acq_rel);
            fam.canceled.fetch_add(1, std::memory_order_relaxed);
        }
    }
    fam.pending.clear();

    // 等待正在执行的任务完成
    m_doneCv.wait(lk, [&] {
        return fam.outstanding.load(std::memory_order_acquire) == 0;
    });
    fam.flushReq = false;
    lk.unlock();

    for (auto& cancel_func : to_cancel) {
        try {
            cancel_func();
        } catch (...) {
        }
    }
    return true;
}

void ThreadManager::SetQueueCap(std::size_t cap)
{
    std::lock_guard<std::mutex> lk(m_mtx);
    m_queueCap = cap;
}

void ThreadManager::PrintStats(Handle h)
{
    std::lock_guard<std::mutex> lk(m_mtx);
    auto it = m_families.find(h);
    if (it == m_families.end()) {
        std::println("Family with handle {} not found.", h);
        return;
    }
    auto& fam = it->second;
    // [最终优化] 增加 "近似快照" 提示，更严谨
    std::println("--- Stats for Family '{}' (H:{}) [Approximate Snapshot] ---"
                 "\n  Enqueued:   {}"
                 "\n  Outstanding:{}"
                 "\n  Canceled:   {}"
                 "\n  Exceptions: {}"
                 "\n-----------------------------------------------------",
        fam.name,
        h,
        fam.enqueued.load(),
        fam.outstanding.load(),
        fam.canceled.load(),
        fam.exceptions.load());
}

void ThreadManager::WorkerLoop()
{
    while (true) {
        QItem job;
        Family* fam_ptr = nullptr;

        {
            std::unique_lock<std::mutex> lk(m_mtx);
            m_cv.wait(lk, [&] { return m_stop.load(std::memory_order_relaxed) || !m_queue.empty(); });

            // [最终优化] 采纳专家建议：一旦收到停止信号，worker 立即退出。
            // 析构函数会负责清理队列中剩余的任务。
            if (m_stop.load(std::memory_order_relaxed)) {
                break;
            }

            // 仅在未停止且队列非空时才执行到这里
            job = std::move(m_queue.front());
            m_queue.pop_front();

            // [教学增强] 在持有锁时就检查家族是否存在
            auto it = m_families.find(job.h);
            if (it == m_families.end()) {
                // 家族已被注销，任务应被取消
                if (job.cancel) {
                    lk.unlock(); // 释放锁再调用用户回调
                    try {
                        job.cancel();
                    } catch (...) {
                    }
                }
                // 注意：此处无法递减 outstanding，因为 fam 无效。
                // 这是一个设计上的权衡，在教学版中是可接受的。
                continue;
            }
            fam_ptr = &it->second;
        }

        bool is_expired = job.deadline.time_since_epoch().count() != 0 && std::chrono::steady_clock::now() > job.deadline;

        if (fam_ptr->flushReq || is_expired) {
            if (job.cancel) {
                try {
                    job.cancel();
                } catch (...) {
                }
            }
            fam_ptr->canceled.fetch_add(1, std::memory_order_relaxed);
        } else {
            try {
                if (job.func)
                    job.func();
            } catch (...) {
                fam_ptr->exceptions.fetch_add(1, std::memory_order_relaxed);
            }
        }

        if (fam_ptr->outstanding.fetch_sub(1, std::memory_order_acq_rel) == 1) {
            std::lock_guard<std::mutex> lk(m_mtx);
            m_doneCv.notify_all();
        }

        if (fam_ptr->addInOrder) {
            std::lock_guard<std::mutex> lk(m_mtx);
            auto it = m_families.find(job.h);
            // [健壮性修复] 在重新加锁后，必须重新检查家族是否存在
            if (it != m_families.end() && job.seq == it->second.nextSeq) {
                auto& fam = it->second;
                fam.nextSeq++;
                auto it_pending = fam.pending.find(fam.nextSeq);
                if (it_pending != fam.pending.end()) {
                    for (auto& pending_job : it_pending->second) {
                        EnqueueUnderLock(std::move(pending_job));
                    }
                    fam.pending.erase(it_pending);
                }
            }
        }
    }
}