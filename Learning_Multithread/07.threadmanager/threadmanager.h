#pragma once

// 学习友好版线程池（最小修改补丁版）
// 改动点：优先级入队、队列上限、析构期软Flush、旧序号取消、通知优化、拒绝即回收

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <cstddef>
#include <cstdint>
#include <deque>
#include <functional>
#include <limits>
#include <map>
#include <mutex>
#include <string>
#include <thread>
#include <unordered_map>
#include <utility>
#include <vector>

class ThreadManager
{
public:
    enum class Priority { High,
        Default };

    using Handle = std::uint32_t;
    using JobFunc = std::function<void(void*)>;
    using CancelFunc = std::function<void(void*)>;

    template<class T> static inline CancelFunc DeleteAs()
    {
        return [](void* p) noexcept { delete static_cast<T*>(p); };
    }

    static constexpr std::uint64_t kWaitForever = std::numeric_limits<std::uint64_t>::max();

    explicit ThreadManager(std::size_t threadCount = std::thread::hardware_concurrency());
    ~ThreadManager();

    // 注册作业家族
    // addInOrder=true：按序放行（基于 seq 与 nextSeq）
    // maxOutOfOrderWindow：乱序窗口（>0 时限制 pending 最大“未来间隙”）
    // cancel：任务被丢弃/过期/Flush 时释放资源（可空）
    [[nodiscard]] bool RegisterJobFamily(const JobFunc& fn,
        const std::string& name,
        Handle* outHandle,
        bool addInOrder = false,
        std::size_t maxOutOfOrderWindow = 0,
        CancelFunc cancel = nullptr);

    // 提交任务（deadline==time_point{} 表示无过期）
    [[nodiscard]] bool PostJob(Handle h,
        void* userData,
        std::uint64_t sequence = 0,
        Priority prio = Priority::Default,
        std::chrono::steady_clock::time_point deadline = {});

    // 等待某家族完成（队列+缓存+执行中全部清空）
    void Sync(Handle h);
    // 限时等待：true=完成，false=超时或家族不存在
    [[nodiscard]] bool SyncFor(Handle h, std::chrono::milliseconds timeout);

    // Flush：丢弃队列和 pending 中尚未执行的任务，等待运行中的任务结束
    // 返回 false 表示家族不存在
    [[nodiscard]] bool Flush(Handle h);

    // 可选的全局队列上限（0=不限制）。仅限制外部 Post；pending 顺延不受此限。
    void SetQueueCap(std::size_t cap) { m_queueCap = cap; }

private:
    struct QItem {
        Handle h;
        JobFunc func;
        void* data;
        std::uint64_t seq;
        Priority prio;
        std::chrono::steady_clock::time_point deadline; // 过期时间（可选）
    };

    struct Family {
        JobFunc func;
        CancelFunc cancel;
        std::string name;
        bool addInOrder = false;
        std::size_t maxWindow = 0; // 乱序窗口（0=不限制）
        std::uint64_t nextSeq = 0; // 期望的下一个序号（仅 addInOrder=true 有效）

        // 待放行缓存：sequence -> 多个任务（通常为 1，用 vector 更稳）
        std::map<std::uint64_t, std::vector<QItem>> pending;

        // 计数/统计
        std::atomic<std::size_t> outstanding { 0 }; // 在途（队列+缓存+执行中）
        std::atomic<std::size_t> enqueued { 0 };
        std::atomic<std::size_t> canceled { 0 };
        std::atomic<std::size_t> exceptions { 0 };

        bool flushReq = false; // Flush 阶段拒绝新任务
    };

private:
    void workerLoop();
    void enqueueNoLock(QItem && it);

private:
    // 全局状态
    std::vector<std::thread> m_workers;
    std::deque<QItem> m_queue; // 全局队列（仅一把锁保护）
    std::size_t m_queueCap { 0 }; // 队列上限（0=不限制）

    std::unordered_map<Handle, Family> m_families;

    std::mutex m_mtx; // 统一大锁：保护队列与家族元数据
    std::condition_variable m_cv; // worker 等待“有任务或停止”
    std::condition_variable m_doneCv; // Sync/Flush 等待“家族 outstanding==0”

    std::atomic<bool> m_stop { false }; // 设置后 worker 退出（跑完队列）
    Handle m_nextHandle { 1 }; // 0 作为非法句柄
};