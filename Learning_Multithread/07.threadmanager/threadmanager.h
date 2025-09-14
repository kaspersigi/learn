// ============================
// file: threadmanager.h
// 说明：一个经过现代化重构的基础线程池 (最终教学版)
// 核心逻辑与原版 threadmanager 保持一致，但API更安全、更现代。
// - 拥抱 RAII：使用构造/析构函数管理生命周期，推荐用智能指针持有。
// - 类型安全：使用 std::function<void()> 替代 void*，杜绝类型转换错误。
// - 自动内存管理：通过 lambda 捕获智能指针，实现任务数据的自动回收。
// - 保持简洁：核心并发模型依旧是“单队列 + 全局锁”，易于理解。
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
    enum class Priority {
        High,
        Default,
    };

    // 家族句柄类型（0 作为非法句柄）
    using Handle = std::uint32_t;
    // 现代化的任务函数签名，无参数，通过 lambda 捕获上下文
    using JobFunc = std::function<void()>;
    // 现代化的取消回调签名
    using CancelFunc = std::function<void()>;

    // 构造函数：创建并启动线程池
    explicit ThreadManager(const std::string& name = "ThreadManager",
        std::size_t numThreads = std::thread::hardware_concurrency());

    // 析构函数：自动停止并清理所有线程和任务
    ~ThreadManager();

    // 禁止拷贝与移动
    ThreadManager(const ThreadManager&) = delete;
    ThreadManager& operator = (const ThreadManager&) = delete;
    ThreadManager(ThreadManager&&) = delete;
    ThreadManager& operator = (ThreadManager&&) = delete;

    // 注册一个作业家族
    [[nodiscard]] bool RegisterJobFamily(const std::string& name,
        Handle* outHandle,
        bool addInOrder = false,
        std::size_t maxOutOfOrderWindow = 0);

    // 提交任务 (类型安全版本)
    [[nodiscard]] bool PostJob(Handle h,
        JobFunc && job,
        std::uint64_t sequence = 0,
        Priority prio = Priority::Default,
        std::chrono::steady_clock::time_point deadline = {},
        CancelFunc&& onCancel = nullptr);

    // 等待指定家族在途任务清零
    void Sync(Handle h);

    // 限时等待指定家族在途任务清零
    [[nodiscard]] bool SyncFor(Handle h, std::chrono::milliseconds timeout);

    // Flush：清空待处理任务，并等待运行中任务结束
    [[nodiscard]] bool Flush(Handle h);

    // 设置全局队列上限
    void SetQueueCap(std::size_t cap);

    // [教学增强] 打印指定家族的统计信息
    void PrintStats(Handle h);

private:
    struct QItem {
        Handle h;
        JobFunc func;
        CancelFunc cancel;
        std::uint64_t seq;
        Priority prio;
        std::chrono::steady_clock::time_point deadline;
    };

    struct Family {
        std::string name;
        bool addInOrder = false;
        std::size_t maxWindow = 0;
        std::uint64_t nextSeq = 0;

        std::map<std::uint64_t, std::vector<QItem>> pending;

        std::atomic<std::size_t> outstanding { 0 };
        std::atomic<std::size_t> enqueued { 0 };
        std::atomic<std::size_t> canceled { 0 };
        std::atomic<std::size_t> exceptions { 0 };

        bool flushReq = false;
    };

private:
    void WorkerLoop();
    // [命名清晰] 调用者必须已持有 m_mtx 锁
    void EnqueueUnderLock(QItem && it);

    std::string m_name;
    std::size_t m_numThreads { 0 };
    std::vector<std::thread> m_workers;
    std::deque<QItem> m_queue;
    std::size_t m_queueCap { 0 };

    std::unordered_map<Handle, Family> m_families;

    std::mutex m_mtx;
    std::condition_variable m_cv;
    std::condition_variable m_doneCv;

    std::atomic<bool> m_stop { false };
    std::atomic<Handle> m_nextHandle { 1 };
};