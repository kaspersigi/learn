// ============================
// 文件: threadmanager.h
// 说明：现代化重构的基础线程池（最终教学版）
// 核心目标：在保持原版 threadmanager 并发模型（单队列+全局锁）的前提下，
//          通过现代 C++ 特性（RAII、智能指针、lambda、原子操作等）提升安全性、可读性与可维护性。
// 关键特性：
//   - RAII 生命周期管理：构造时启动线程，析构时自动清理，避免资源泄漏。
//   - 类型安全任务：使用 std::function<void()> 替代原始 void* 回调，杜绝强制类型转换风险。
//   - 自动内存回收：通过 lambda 捕获智能指针，任务数据随 lambda 自动释放。
//   - 任务家族机制：支持按家族分组任务，可独立同步、限流、统计。
//   - 优先级与超时：支持高优先级插队、任务截止时间、取消回调。
//   - 教学友好：保留简单并发模型，适合理解多线程基础与生产者-消费者模式。
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

class ThreadManager {
public:
    // 任务优先级枚举：高优先级任务会被插入队列头部，优先执行
    enum class Priority {
        High, // 高优先级，插入队列头部
        Default, // 默认优先级，追加到队列尾部
    };

    // 家族句柄类型：用于标识任务家族，0 表示非法句柄（保留值）
    using Handle = std::uint32_t;
    // 任务函数类型：无参数无返回值，通过 lambda 捕获上下文实现类型安全
    using JobFunc = std::function<void()>;
    // 取消回调函数类型：当任务被取消或超时时调用，用于资源清理
    using CancelFunc = std::function<void()>;

    // 构造函数：创建线程池并启动工作线程
    // 参数：
    //   name: 线程池名称，用于调试和日志（默认 "ThreadManager"）
    //   numThreads: 工作线程数量，默认为硬件并发数（若为0则设为1）
    explicit ThreadManager(const std::string& name = "ThreadManager",
        std::size_t numThreads = std::thread::hardware_concurrency());

    // 析构函数：自动停止所有线程，清理队列中未执行任务，调用取消回调
    // 保证线程安全退出，避免析构时仍有线程访问已销毁对象
    ~ThreadManager();

    // 禁用拷贝与移动语义：线程池是独占资源，不可复制或转移
    ThreadManager(const ThreadManager&) = delete;
    ThreadManager& operator=(const ThreadManager&) = delete;
    ThreadManager(ThreadManager&&) = delete;
    ThreadManager& operator=(ThreadManager&&) = delete;

    // 注册一个任务家族（Job Family）
    // 任务家族用于对任务分组管理，可独立同步、设置顺序性、统计性能
    // 参数：
    //   name: 家族名称（用于调试）
    //   outHandle: 输出参数，返回分配的家族句柄（必须非空）
    //   addInOrder: 是否启用顺序执行（默认 false）
    //   maxOutOfOrderWindow: 若启用顺序执行，允许的最大乱序窗口（超出则拒绝任务）
    // 返回值：
    //   true: 注册成功
    //   false: 句柄无效或分配失败
    [[nodiscard]] bool RegisterJobFamily(const std::string& name,
        Handle* outHandle,
        bool addInOrder = false,
        std::size_t maxOutOfOrderWindow = 0);

    // 提交一个任务到指定家族
    // 参数：
    //   h: 家族句柄（必须已注册）
    //   job: 任务函数（必须非空）
    //   sequence: 任务序列号（仅在 addInOrder=true 时有效，用于控制执行顺序）
    //   prio: 任务优先级（默认 Default）
    //   deadline: 任务截止时间（超时则取消，不执行）
    //   onCancel: 取消回调（任务被拒绝、取消或超时时调用）
    // 返回值：
    //   true: 任务成功入队
    //   false: 任务被拒绝（家族不存在、队列满、序列号无效等）
    [[nodiscard]] bool PostJob(Handle h,
        JobFunc&& job,
        std::uint64_t sequence = 0,
        Priority prio = Priority::Default,
        std::chrono::steady_clock::time_point deadline = {},
        CancelFunc&& onCancel = nullptr);

    // 同步等待：阻塞直到指定家族所有已提交任务（包括队列中和正在执行的）全部完成
    // 注意：不会取消或跳过任务，只是等待它们自然结束
    void Sync(Handle h);

    // 限时同步等待：在指定超时时间内等待家族任务完成
    // 返回值：
    //   true: 在超时前完成
    //   false: 超时或家族不存在
    [[nodiscard]] bool SyncFor(Handle h, std::chrono::milliseconds timeout);

    // Flush 操作：立即取消家族所有待执行任务（队列中 + pending 中），并等待正在执行的任务完成
    // 注意：正在执行的任务不会被中断，但完成后不再调度后续 pending 任务
    // 返回值：
    //   true: 操作成功
    //   false: 家族不存在
    [[nodiscard]] bool Flush(Handle h);

    // 设置全局任务队列容量上限（0 表示无限制）
    // 当队列满时，新提交的任务将被拒绝（调用 onCancel）
    void SetQueueCap(std::size_t cap);

    // [教学增强] 打印指定家族的统计信息（近似快照，非精确值）
    // 输出：已入队数、进行中数、已取消数、异常数
    void PrintStats(Handle h);

private:
    // 任务队列中的单个元素结构体
    struct QItem {
        Handle h; // 所属家族句柄
        JobFunc func; // 任务函数
        CancelFunc cancel; // 取消回调函数
        std::uint64_t seq; // 序列号（用于顺序控制）
        Priority prio; // 优先级
        std::chrono::steady_clock::time_point deadline; // 截止时间（0 表示无限制）
    };

    // 任务家族结构体：管理一组相关任务的元数据和状态
    struct Family {
        std::string name; // 家族名称（调试用）
        bool addInOrder = false; // 是否启用顺序执行
        std::size_t maxWindow = 0; // 最大允许的乱序窗口（仅当 addInOrder=true 时有效）
        std::uint64_t nextSeq = 0; // 下一个期望执行的序列号（用于顺序调度）

        // 乱序任务暂存区：key=序列号，value=该序列号对应的所有任务（通常为1个）
        std::map<std::uint64_t, std::vector<QItem>> pending;

        // 统计计数器（原子操作，线程安全）
        std::atomic<std::size_t> outstanding { 0 }; // 当前进行中任务数（含队列中+执行中）
        std::atomic<std::size_t> enqueued { 0 }; // 总共成功入队任务数
        std::atomic<std::size_t> canceled { 0 }; // 被取消/拒绝的任务数
        std::atomic<std::size_t> exceptions { 0 }; // 执行时抛出异常的任务数

        bool flushReq = false; // 是否收到 Flush 请求（收到后新任务将被拒绝）
    };

private:
    // 工作线程主循环函数：从队列取任务并执行
    void WorkerLoop();
    // 在已持有 m_mtx 锁的前提下，将任务加入主队列（根据优先级决定插入位置）
    // 仅内部调用，外部不可直接访问
    void EnqueueUnderLock(QItem&& it);

    // 成员变量区 —— 所有成员均在线程安全保护下访问（通过 m_mtx）

    std::string m_name; // 线程池名称
    std::size_t m_numThreads { 0 }; // 工作线程数量
    std::vector<std::thread> m_workers; // 工作线程容器
    std::deque<QItem> m_queue; // 全局任务队列（主线程安全队列）
    std::size_t m_queueCap { 0 }; // 队列容量上限（0=无限制）

    // 家族映射表：句柄 -> 家族结构
    std::unordered_map<Handle, Family> m_families;

    // 同步原语
    std::mutex m_mtx; // 全局互斥锁（保护 m_queue, m_families 等）
    std::condition_variable m_cv; // 任务队列条件变量（通知 worker 有新任务）
    std::condition_variable m_doneCv; // 完成通知条件变量（用于 Sync/Flush 等待）

    // 控制标志
    std::atomic<bool> m_stop { false }; // 停止标志（通知所有 worker 退出）
    std::atomic<Handle> m_nextHandle { 1 }; // 下一个可用家族句柄（从1开始，0为非法）
};