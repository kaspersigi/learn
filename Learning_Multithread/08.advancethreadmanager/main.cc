// ============================
// 文件: main.cc（演示）
// 说明：展示 AdvanceThreadManager 的现代化用法（最终教学版）
// 演示内容：
//   - RAII 生命周期管理（unique_ptr 自动析构）
//   - 类型安全任务提交（lambda + shared_ptr）
//   - 有序家族的严格按序执行
//   - 无序家族的优先级、超时、队列上限
//   - Flush 与 Sync 的行为差异
// 教学目标：帮助学习者掌握生产级线程池的正确使用方式
// ============================

#include "advancethreadmanager.h"
#include <chrono>
#include <memory> // 用于 std::make_shared / std::unique_ptr
#include <print> // C++23 标准输出
#include <thread>

// --- 演示用数据结构 ---
// Payload：每个任务携带的数据（模拟真实业务负载）
struct Payload {
    int v; // 任务编号或负载值
    const char* tag; // 任务家族标签，用于日志区分
};

// --- 任务执行函数 ---
auto myJob(Payload* p) -> void
{
    if (!p)
        return;
    std::this_thread::sleep_for(std::chrono::milliseconds(10)); // 模拟耗时操作
    std::println("[{}] job {} done", p->tag, p->v);
}

// --- 任务取消回调函数 ---
auto myCancel(Payload* p) -> void
{
    if (!p)
        return;
    std::println("[{}] Job {} cancelled.", p->tag, p->v);
}

// --- 主函数：演示线程池完整用法 ---
auto main(int argc, char* argv[]) -> int
{
    // >>> 第一步：创建线程池 <<<
    // 使用 unique_ptr 管理生命周期，确保析构时自动清理
    auto threadPool = std::make_unique<AdvanceThreadManager>("PerfThreadPool", 4);

    // 设置全局队列容量上限为 8（用于演示任务被拒绝）
    threadPool->SetQueueCap(8);

    // >>> 第二步：演示家族 A —— 有序任务家族 <<<
    AdvanceThreadManager::Handle hA = 0;
    // 注册家族 A：启用顺序执行，最大乱序窗口为 8
    threadPool->RegisterJobFamily("family-A", &hA, /*addInOrder*/ true, /*maxWindow*/ 8);

    // 定义一个辅助 lambda，简化有序任务提交
    auto postOrderedJob = [&](int val, int seq) {
        // 使用 shared_ptr 管理 Payload 生命周期
        auto p = std::make_shared<Payload>(Payload { val, "A" });

        // 提交任务：任务函数和取消回调都按值捕获 p（增加引用计数）
        threadPool->PostJob(
            hA,
            [p]() { myJob(p.get()); }, // 任务执行体
            seq, // 序列号
            AdvanceThreadManager::Priority::Default,
            {},
            [p]() { myCancel(p.get()); } // 取消回调
        );
        // p 的生命周期由两个 lambda 共享，任一执行后引用计数减1，最终自动释放
    };

    // 乱序提交任务 0~5，执行顺序应为 0,1,2,3,4,5
    postOrderedJob(2, 2);
    postOrderedJob(0, 0);
    postOrderedJob(1, 1);
    postOrderedJob(5, 5);
    postOrderedJob(4, 4);
    postOrderedJob(3, 3);

    // 等待家族 A 所有任务按序完成
    threadPool->Sync(hA);
    std::println("[A] sync done");

    // 演示 Flush：提交两个新任务然后立即 Flush
    postOrderedJob(6, 6);
    postOrderedJob(7, 7);
    threadPool->Flush(hA); // 6 和 7 将被取消
    std::println("[A] flush done");

    // >>> 第三步：演示家族 B —— 无序任务家族 <<<
    AdvanceThreadManager::Handle hB = 0;
    threadPool->RegisterJobFamily("family-B", &hB); // 无序模式

    // 定义辅助 lambda，简化无序任务提交
    auto postUnorderedJob = [&](int val, const char* tag, AdvanceThreadManager::Priority prio = AdvanceThreadManager::Priority::Default, std::chrono::steady_clock::time_point deadline = {}) {
        auto p = std::make_shared<Payload>(Payload { val, tag });
        threadPool->PostJob(
            hB,
            [p]() { myJob(p.get()); },
            0, // sequence 无意义（无序家族）
            prio,
            deadline,
            [p]() { myCancel(p.get()); });
    };

    // 提交 4 个普通任务
    for (int i = 100; i < 104; ++i) {
        postUnorderedJob(i, "B");
    }

    // 提交 1 个高优先级任务（应优先执行）
    postUnorderedJob(999, "B-HIGH", AdvanceThreadManager::Priority::High);

    // 提交 1 个已过期任务（应立即被取消）
    auto past = std::chrono::steady_clock::now() - std::chrono::milliseconds(1);
    postUnorderedJob(555, "B-EXP", AdvanceThreadManager::Priority::Default, past);

    // 提交 20 个任务（触发队列上限，部分任务将被拒绝）
    for (int i = 200; i < 220; ++i) {
        postUnorderedJob(i, "B");
    }

    // 等待家族 B 所有任务完成（观察高优先级、超时、队列上限的效果）
    threadPool->Sync(hB);
    std::println("[B] sync done (cap/priority/deadline demo)");

    // >>> 第四步：线程池自动析构 <<<
    // 离开作用域，unique_ptr 自动调用析构函数
    // 析构函数会：
    //   1. 停止所有工作线程
    //   2. 清理残留任务
    //   3. 调用 onCancel 回调
    std::println("\nThread pool will be destroyed automatically by unique_ptr.");

    return 0;
}