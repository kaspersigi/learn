// ============================
// file: advancethreadmanager.h
// 说明：生产级高性能线程池/任务调度器
// [核心特性]
// - 高性能调度：采用“工作窃取”(Work-Stealing)模式，每个 Worker 拥有独立队列，极大降低锁竞争。
// - 类型安全：API 全面采用 std::function<void()>，杜绝 void* 和不安全的类型转换。
// - 现代化生命周期管理：遵循 RAII 原则，使用构造/析构函数管理资源，推荐由智能指针持有。
// - 作业家族 (Family)：保留并优化了家族概念，用于任务分组与统计。
// - 严格按序执行：为有序家族提供严格的“按序完成”保证。
// [保留功能]
// - 优先级、超时/过期、乱序窗口、队列上限、Flush/Sync 等高级功能。
// [锁策略]
// - 细粒度锁：用多把锁替代全局大锁。家族管理使用读写锁，每个 Worker 队列有独立锁。
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
#include <random>
#include <shared_mutex>
#include <string>
#include <thread>
#include <unordered_map>
#include <utility>
#include <vector>

class AdvanceThreadManager
{
public:
    // 任务优先级：High 将进入队列头部，Default 进入尾部
    enum class Priority {
        High,
        Default,
    };

    // 家族句柄类型（0 作为非法句柄）
    using Handle = std::uint32_t;

    // 任务函数签名：采用 std::function<void()> 实现类型安全
    using JobFunc = std::function<void()>;

    // 取消回调：同样采用类型安全的方式
    using CancelFunc = std::function<void()>;

    // 无限等待占位常量
    static constexpr std::uint64_t kWaitForever = std::numeric_limits<std::uint64_t>::max();

    // 构造函数：创建并启动线程池
    // - name: 线程池名称，用于日志和调试
    // - numThreads: 线程池大小，默认为硬件核心数
    explicit AdvanceThreadManager(const std::string& name = "AdvanceThreadManager",
        std::size_t numThreads = std::thread::hardware_concurrency());

    // 析构函数：安全地停止并清理所有资源
    ~AdvanceThreadManager();

    // 禁止拷贝与移动
    AdvanceThreadManager(const AdvanceThreadManager&) = delete;
    AdvanceThreadManager& operator = (const AdvanceThreadManager&) = delete;
    AdvanceThreadManager(AdvanceThreadManager&&) = delete;
    AdvanceThreadManager& operator = (AdvanceThreadManager&&) = delete;

    // 注册一个作业家族
    // - fn：(可选) 家族统一的执行函数，如果 PostJob 时提供了具体任务，则此参数可忽略
    // - name：家族名（用于诊断/统计）
    // - outHandle：输出家族句柄（必需）
    // - addInOrder：是否按序放行
    // - maxOutOfOrderWindow：当 addInOrder=true 时，允许的“未来序号”窗口
    // - cancel：(可选) 统一的取消回调
    [[nodiscard]] bool RegisterJobFamily(const std::string& name,
        Handle* outHandle,
        bool addInOrder = false,
        std::size_t maxOutOfOrderWindow = 0);

    // 提交任务 (类型安全版本)
    // - h：目标家族
    // - job：要执行的任务函数
    // - sequence：任务序号（用于按序放行）
    // - prio：优先级
    // - deadline：过期时间点
    // - onCancel：任务被取消时执行的回调
    [[nodiscard]] bool PostJob(Handle h,
        JobFunc && job,
        std::uint64_t sequence = 0,
        Priority prio = Priority::Default,
        std::chrono::steady_clock::time_point deadline = {},
        CancelFunc&& onCancel = nullptr);

    // 阻塞等待：指定家族在途任务清零
    void Sync(Handle h);

    // 限时等待：true 表示在超时前完成
    [[nodiscard]] bool SyncFor(Handle h, std::chrono::milliseconds timeout);

    // Flush：拒绝新任务，丢弃未执行项，等待正在执行的任务结束
    [[nodiscard]] bool Flush(Handle h);

    // 设置全局队列上限（0 不限制）
    void SetQueueCap(std::size_t cap);

private:
    // 任务队列中的完整条目
    struct QItem {
        Handle h;
        JobFunc func;
        CancelFunc cancel;
        std::uint64_t seq;
        Priority prio;
        std::chrono::steady_clock::time_point deadline;
    };

    // 每个 Worker 线程拥有的本地任务队列
    struct WorkerQueue {
        std::deque<QItem> q;
        std::mutex mtx;
    };

    // 家族元数据与统计
    struct Family {
        std::string name;
        bool addInOrder = false;
        std::size_t maxWindow = 0;
        std::atomic<std::uint64_t> nextSeq { 0 };

        // 待放行缓存 (仅用于有序家族)
        std::map<std::uint64_t, std::vector<QItem>> pending;
        std::mutex pendingMtx; // 保护 pending map

        // 原子统计
        std::atomic<std::size_t> outstanding { 0 };
        std::atomic<std::size_t> enqueued { 0 };
        std::atomic<std::size_t> canceled { 0 };
        std::atomic<std::size_t> exceptions { 0 };
        std::atomic<bool> flushReq { false };
    };

private:
    void WorkerLoop(std::size_t workerId);
    bool TryGetJob(QItem & job, std::size_t workerId);
    void Enqueue(QItem && it, Handle h_for_ordered_dispatch);
    void EnqueueTo(std::deque<QItem> & q, QItem && it);

private:
    std::string m_name;
    std::size_t m_numThreads { 0 };

    // 线程与队列
    std::vector<std::thread> m_workers;
    std::vector<WorkerQueue> m_workerQueues; // 每个 worker 一个队列
    std::atomic<std::size_t> m_queueCap { 0 };
    std::atomic<std::size_t> m_totalQueued { 0 };

    // 家族表：句柄到 Family 的映射
    std::unordered_map<Handle, Family> m_families;
    std::shared_mutex m_familiesMtx; // 读写锁保护家族表

    // 全局同步机制
    std::mutex m_cvMtx;
    std::condition_variable m_cv;
    std::condition_variable m_doneCv;

    std::atomic<bool> m_stop { false };
    std::atomic<Handle> m_nextHandle { 1 };

    // 用于 work-stealing 和随机分发
    std::mt19937 m_randEngine { std::random_device {}() };
};