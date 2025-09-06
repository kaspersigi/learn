// ============================
// file: threadmanager.h
// 说明：轻量线程池/任务调度器
// - “作业家族”（Family）概念：同一家族共享执行函数与统计数据
// - 可选按序放行：基于 sequence 与 nextSeq 实现严格顺序
// - 乱序窗口：限制未来可缓存的最大“序号间隙”
// - 优先级：High 插队到全局队列头部，Default 进入队列尾部
// - 队列上限：仅限制外部 Post 进入全局队列的数量（pending 不受限）
// - 超时/过期：deadline 超过当前时间的任务会被取消（走 cancel 回调）
// - Flush：丢弃队列与 pending 中未执行任务，等待运行中任务结束
// - Sync/SyncFor：等待指定家族 outstanding（在途计数）归零
// 线程安全：对外 API 除构造/析构外均内部加锁；回调在锁外执行
// ============================

#pragma once

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
    // 任务优先级：High 将进入全局队列头部，Default 进入尾部
    enum class Priority { High,
        Default };

    // 家族句柄类型（0 作为非法句柄）
    using Handle = std::uint32_t;

    // 任务函数签名：入参为用户自定义的指针（由提交者负责语义）
    using JobFunc = std::function<void(void*)>;

    // 取消回调：任务被拒绝/过期/Flush 时用于回收资源（可为空）
    using CancelFunc = std::function<void(void*)>;

    // 工具：返回一个把 void* 当作 T* delete 的取消回调
    template<class T> static inline CancelFunc DeleteAs()
    {
        return [](void* p) noexcept { delete static_cast<T*>(p); };
    }

    // 供外部调用者使用的“无限等待”占位常量（本类内部未直接使用）
    static constexpr std::uint64_t kWaitForever = std::numeric_limits<std::uint64_t>::max();

    // 构造：创建指定数量 worker（最少 1 个）
    explicit ThreadManager(std::size_t threadCount = std::thread::hardware_concurrency());

    // 析构：执行“软 Flush”，使所有未执行任务走取消回调，并回收线程
    ~ThreadManager();

    // 注册一个作业家族
    // - fn：家族统一的执行函数
    // - name：家族名（用于诊断/统计）
    // - outHandle：输出家族句柄（必需）
    // - addInOrder：是否按序放行（基于 seq/nextSeq）
    // - maxOutOfOrderWindow：当 addInOrder=true 时，允许的“未来序号”窗口，0 表示不限制
    // - cancel：取消回调（可为空）
    [[nodiscard]] bool RegisterJobFamily(const JobFunc& fn,
        const std::string& name,
        Handle* outHandle,
        bool addInOrder = false,
        std::size_t maxOutOfOrderWindow = 0,
        CancelFunc cancel = nullptr);

    // 提交任务
    // - h：目标家族
    // - userData：用户数据指针（执行或取消时由回调消费）
    // - sequence：任务序号（用于按序放行；无序家族忽略）
    // - prio：优先级
    // - deadline：过期时间点（默认 0 表示无期限）
    [[nodiscard]] bool PostJob(Handle h,
        void* userData,
        std::uint64_t sequence = 0,
        Priority prio = Priority::Default,
        std::chrono::steady_clock::time_point deadline = {});

    // 阻塞等待：指定家族在途任务（队列+pending+执行中）清零
    void Sync(Handle h);

    // 限时等待：true 表示在超时前完成；false 表示超时或家族不存在
    [[nodiscard]] bool SyncFor(Handle h, std::chrono::milliseconds timeout);

    // Flush：拒绝新任务，丢弃队列与 pending 中未执行项，等待正在执行的任务结束
    // 返回 false 表示家族不存在
    [[nodiscard]] bool Flush(Handle h);

    // 设置全局队列上限（0 不限制）
    // 说明：仅限制“进入全局队列”的数量；pending（未来序号）不受限
    void SetQueueCap(std::size_t cap) { m_queueCap = cap; }

private:
    // 全局队列元素：记录家族/序号/优先级/过期时间等
    struct QItem {
        Handle h;
        JobFunc func;
        void* data;
        std::uint64_t seq;
        Priority prio;
        std::chrono::steady_clock::time_point deadline;
    };

    // 家族元数据与统计
    struct Family {
        JobFunc func; // 家族统一执行函数
        CancelFunc cancel; // 取消回调
        std::string name; // 家族名（仅供诊断）
        bool addInOrder = false; // 是否按序放行
        std::size_t maxWindow = 0; // 乱序窗口（addInOrder 时有效）
        std::uint64_t nextSeq = 0; // 期望下一个可执行的序号

        // 待放行缓存：sequence -> 该序号对应的一批任务（通常只有 1 个，使用 vector 更通用）
        std::map<std::uint64_t, std::vector<QItem>> pending;

        // 原子统计：
        // outstanding：在途计数（队列 + pending + 执行中）；归零意味着该家族“空闲”
        // enqueued：累计提交计数
        // canceled：累计取消计数（包含过期、Flush、被拒等）
        // exceptions：执行阶段抛异常的累计计数
        std::atomic<std::size_t> outstanding { 0 };
        std::atomic<std::size_t> enqueued { 0 };
        std::atomic<std::size_t> canceled { 0 };
        std::atomic<std::size_t> exceptions { 0 };

        // Flush 标记：true 时拒绝新任务，且队列/pending 中的该家族任务被剔除
        bool flushReq = false;
    };

private:
    // worker 主循环：从全局队列取任务 → 判断可执行/缓存/取消 → 调用回调 → 推进 nextSeq
    void workerLoop();

    // 在已持有 m_mtx 的前提下，将任务放入全局队列（处理优先级并通知）
    void enqueueNoLock(QItem && it);

private:
    // 线程与队列
    std::vector<std::thread> m_workers; // 工作线程
    std::deque<QItem> m_queue; // 全局任务队列（单把大锁保护）
    std::size_t m_queueCap { 0 }; // 队列上限（0 不限制）

    // 家族表：句柄到 Family 的映射
    std::unordered_map<Handle, Family> m_families;

    // 互斥与条件变量
    std::mutex m_mtx; // 统一大锁，保护队列与家族元数据
    std::condition_variable m_cv; // worker 等待“有任务或停止”
    std::condition_variable m_doneCv; // Sync/Flush 等待“家族 outstanding==0”

    // 停止标志：true 时 worker 在队列耗尽后退出
    std::atomic<bool> m_stop { false };

    // 家族句柄自增分配（0 保留为非法句柄）
    Handle m_nextHandle { 1 };
};