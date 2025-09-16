// ============================
// 文件: main.cc (for Modern ThreadManager)
// 说明：现代化、类型安全线程池 API 的完整教学演示（最终教学版）
// 演示内容：
//   - 如何创建线程池并设置参数（线程数、队列上限）
//   - 如何注册任务家族（有序 vs 无序）
//   - 如何通过 lambda + 智能指针提交任务（自动内存管理）
//   - 如何使用 Sync、Flush、SyncFor 等同步原语
//   - 如何观察任务执行顺序、优先级、超时取消等行为
//   - 如何打印家族统计信息辅助调试
// 教学目标：帮助学习者理解现代 C++ 线程池的设计哲学与安全实践
// ============================
#include "threadmanager.h"
#include <memory> // 用于 std::make_shared / std::unique_ptr
#include <print> // C++23 标准输出（如不支持可替换为 iostream + cout）
#include <vector>

// --- 演示用数据结构 ---
// Payload：每个任务携带的数据（模拟真实业务负载）
// 包含一个整数值和家族标签，用于区分任务来源和调试输出
struct Payload {
    int v; // 任务编号或负载值
    const char* tag; // 任务家族标签（如 "A"、"B"），用于日志区分
};

// --- 任务执行函数 ---
// 模拟实际任务工作：睡眠一小段时间后打印完成信息
// 参数：Payload 指针（由 lambda 捕获的 shared_ptr 自动管理生命周期）
auto myJob(Payload* p) -> void
{
    if (!p)
        return; // 安全检查：防止空指针（虽然 lambda 捕获应保证非空）
    std::this_thread::sleep_for(std::chrono::milliseconds(10)); // 模拟耗时操作
    std::println("[{}] job {} done", p->tag, p->v); // 打印任务完成日志
}

// --- 任务取消回调函数 ---
// 当任务被拒绝、Flush 或超时时调用，用于资源清理或日志记录
// 参数：Payload 指针（由 lambda 捕获的 shared_ptr 自动管理生命周期）
auto myCancel(Payload* p) -> void
{
    if (!p)
        return;
    std::println("[{}] Job {} cancelled.", p->tag, p->v); // 打印取消日志
}

// --- 主函数：演示线程池完整用法 ---
auto main(int argc, char* argv[]) -> int
{
    // >>> 第一步：创建线程池 <<<
    // 使用 std::unique_ptr 管理生命周期，确保析构时自动清理线程与任务
    // 参数：名称 "MainThreadPool"，线程数 4（可自定义）
    auto threadPool = std::make_unique<ThreadManager>("MainThreadPool", 4);
    // 设置全局队列容量上限为 8（超过则拒绝新任务，调用 onCancel）
    threadPool->SetQueueCap(8);

    // >>> 第二步：演示家族 A —— 有序任务家族 <<<
    ThreadManager::Handle hA = 0; // 初始化家族句柄
    // 注册家族 A：启用顺序执行，最大乱序窗口为 8（允许 sequence 超前最多 8 个）
    threadPool->RegisterJobFamily("family-A", &hA, /*addInOrder*/ true, /*maxWindow*/ 8);

    // 定义一组乱序提交的任务序列（模拟现实中的乱序到达）
    std::vector<int> order = {
        2,
        0,
        1,
        5,
        4,
        3,
    };

    // 循环提交任务：每个任务携带 Payload，并通过 lambda 捕获 shared_ptr
    for (int i : order) {
        // 创建任务数据（智能指针自动管理内存）
        auto p = std::make_shared<Payload>(i, "A");
        // 提交任务到家族 A
        threadPool->PostJob(
            hA, // 家族句柄
            [p]() { myJob(p.get()); }, // 任务函数（捕获 p，自动延长生命周期）
            i, // 序列号（用于顺序控制）
            ThreadManager::Priority::Default, // 优先级（默认）
            {}, // 截止时间（无限制）
            [p]() { myCancel(p.get()); } // 取消回调（同样捕获 p）
        );
        // 注意：p 的生命周期由 lambda 捕获延长，任务执行或取消后自动释放
    }

    // 等待家族 A 所有任务完成（按 sequence 顺序执行：0,1,2,3,4,5）
    std::println("[A] All jobs posted. Waiting for sync...");
    threadPool->Sync(hA); // 阻塞直到 outstanding 降为 0
    std::println("[A] sync done");

    // [教学增强] 打印家族 A 的统计信息（观察入队数、取消数等）
    threadPool->PrintStats(hA);

    // >>> 第三步：演示 Flush 功能 <<<
    {
        // 提交两个新任务（sequence=6 和 7）
        auto p6 = std::make_shared<Payload>(6, "A");
        auto p7 = std::make_shared<Payload>(7, "A");
        threadPool->PostJob(hA, [p6]() { myJob(p6.get()); }, 6, ThreadManager::Priority::Default, {}, [p6]() { myCancel(p6.get()); });
        threadPool->PostJob(hA, [p7]() { myJob(p7.get()); }, 7, ThreadManager::Priority::Default, {}, [p7]() { myCancel(p7.get()); });
    }
    // 调用 Flush：取消家族 A 所有待执行任务（6 和 7 将被取消），并等待正在执行的任务完成
    threadPool->Flush(hA);
    std::println("[A] flush done");
    // 再次打印统计：观察 canceled 计数增加
    threadPool->PrintStats(hA);

    // >>> 第四步：演示家族 B —— 无序任务家族 <<<
    ThreadManager::Handle hB = 0;
    // 注册家族 B：不启用顺序执行（默认行为）
    threadPool->RegisterJobFamily("family-B", &hB);

    // 提交 4 个普通任务（sequence=0，无意义，因为无序）
    for (int i = 100; i < 104; ++i) {
        auto p = std::make_shared<Payload>(i, "B");
        threadPool->PostJob(hB, [p]() { myJob(p.get()); }, 0, ThreadManager::Priority::Default, {}, [p]() { myCancel(p.get()); });
    }

    // 提交一个高优先级任务（会被插入队列头部，优先执行）
    {
        auto p = std::make_shared<Payload>(999, "B-HIGH");
        threadPool->PostJob(hB, [p]() { myJob(p.get()); }, 0, ThreadManager::Priority::High, {}, [p]() { myCancel(p.get()); });
    }

    // 提交一个已过期任务（deadline 在过去），应被立即取消
    {
        auto p = std::make_shared<Payload>(555, "B-EXP");
        auto past = std::chrono::steady_clock::now() - std::chrono::milliseconds(1); // 设置为1毫秒前
        threadPool->PostJob(hB, [p]() { myJob(p.get()); }, 0, ThreadManager::Priority::Default, past, [p]() { myCancel(p.get()); });
    }

    // 再提交 20 个普通任务（测试队列容量与优先级调度）
    for (int i = 200; i < 220; ++i) {
        auto p = std::make_shared<Payload>(i, "B");
        threadPool->PostJob(hB, [p]() { myJob(p.get()); }, 0, ThreadManager::Priority::Default, {}, [p]() { myCancel(p.get()); });
    }

    // [教学增强] 演示 SyncFor 超时行为
    std::println("\n[B] Trying SyncFor with a short timeout (will likely fail)...");
    bool success = threadPool->SyncFor(hB, std::chrono::milliseconds(10)); // 等待10毫秒
    std::println("[B] SyncFor {}", success ? "succeeded" : "timed out"); // 应超时失败

    // 等待家族 B 所有任务最终完成（包括高优先级和普通任务）
    std::println("[B] Waiting for final sync...");
    threadPool->Sync(hB);
    std::println("[B] sync done (cap/priority/deadline demo)");

    // 打印家族 B 统计：观察 enqueued、canceled（应包含超时任务）、exceptions 等
    threadPool->PrintStats(hB);

    // >>> 第五步：线程池自动析构 <<<
    // 由于使用 unique_ptr，离开作用域时自动调用析构函数
    // 析构函数会：
    //   1. 停止所有工作线程
    //   2. 清理队列中残留任务
    //   3. 调用所有未执行任务的 onCancel 回调
    std::println("\nThread pool will be destroyed automatically by unique_ptr.");

    // 程序正常退出
    return 0;
}