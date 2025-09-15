// ============================
// file: main.cc (for Modern ThreadManager)
// 说明：展示现代化、类型安全的线程池 API 用法 (最终教学版)
// ============================
#include "threadmanager.h"
#include <memory>
#include <print>
#include <vector>

// 演示用负载：携带一个整数与家族标签
struct Payload {
    int v;
    const char* tag;
};

// 任务执行体
auto myJob(Payload* p) -> void
{
    if (!p)
        return;
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::println("[{}] job {} done", p->tag, p->v);
}

// 取消回调体
auto myCancel(Payload* p) -> void
{
    if (!p)
        return;
    std::println("[{}] Job {} cancelled.", p->tag, p->v);
}

auto main(int argc, char* argv[]) -> int
{
    auto threadPool = std::make_unique<ThreadManager>("MainThreadPool", 4);
    threadPool->SetQueueCap(8);

    // ---- 家族 A（有序）----
    ThreadManager::Handle hA = 0;
    threadPool->RegisterJobFamily("family-A", &hA, /*addInOrder*/ true, /*maxWindow*/ 8);

    std::vector<int> order = {
        2,
        0,
        1,
        5,
        4,
        3,
    };
    for (int i : order) {
        auto p = std::make_shared<Payload>(i, "A");
        threadPool->PostJob(
            hA,
            [p]() { myJob(p.get()); },
            i,
            ThreadManager::Priority::Default,
            {},
            [p]() { myCancel(p.get()); });
    }

    std::println("[A] All jobs posted. Waiting for sync...");
    threadPool->Sync(hA);
    std::println("[A] sync done");
    threadPool->PrintStats(hA); // [教学增强] 打印统计信息

    // 演示 Flush
    {
        auto p6 = std::make_shared<Payload>(6, "A");
        auto p7 = std::make_shared<Payload>(7, "A");
        threadPool->PostJob(hA, [p6]() { myJob(p6.get()); }, 6, ThreadManager::Priority::Default, {}, [p6]() { myCancel(p6.get()); });
        threadPool->PostJob(hA, [p7]() { myJob(p7.get()); }, 7, ThreadManager::Priority::Default, {}, [p7]() { myCancel(p7.get()); });
    }
    threadPool->Flush(hA);
    std::println("[A] flush done");
    threadPool->PrintStats(hA);

    // ---- 家族 B（无序）----
    ThreadManager::Handle hB = 0;
    threadPool->RegisterJobFamily("family-B", &hB);

    for (int i = 100; i < 104; ++i) {
        auto p = std::make_shared<Payload>(i, "B");
        threadPool->PostJob(hB, [p]() { myJob(p.get()); }, 0, ThreadManager::Priority::Default, {}, [p]() { myCancel(p.get()); });
    }
    {
        auto p = std::make_shared<Payload>(999, "B-HIGH");
        threadPool->PostJob(hB, [p]() { myJob(p.get()); }, 0, ThreadManager::Priority::High, {}, [p]() { myCancel(p.get()); });
    }
    {
        auto p = std::make_shared<Payload>(555, "B-EXP");
        auto past = std::chrono::steady_clock::now() - std::chrono::milliseconds(1);
        threadPool->PostJob(hB, [p]() { myJob(p.get()); }, 0, ThreadManager::Priority::Default, past, [p]() { myCancel(p.get()); });
    }
    for (int i = 200; i < 220; ++i) {
        auto p = std::make_shared<Payload>(i, "B");
        threadPool->PostJob(hB, [p]() { myJob(p.get()); }, 0, ThreadManager::Priority::Default, {}, [p]() { myCancel(p.get()); });
    }

    // [教学增强] 演示 SyncFor 超时
    std::println("\n[B] Trying SyncFor with a short timeout (will likely fail)...");
    bool success = threadPool->SyncFor(hB, std::chrono::milliseconds(10));
    std::println("[B] SyncFor {}", success ? "succeeded" : "timed out");

    std::println("[B] Waiting for final sync...");
    threadPool->Sync(hB);
    std::println("[B] sync done (cap/priority/deadline demo)");
    threadPool->PrintStats(hB);

    std::println("\nThread pool will be destroyed automatically by unique_ptr.");

    return 0;
}