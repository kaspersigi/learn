// ============================
// file: main.cc (for Modern ThreadManager)
// 说明：展示现代化、类型安全的线程池 API 用法 (最终教学版)
// ============================
#include "threadmanager.h"
#include <iostream>
#include <memory>
#include <vector>

// 演示用负载：携带一个整数与家族标签
struct Payload {
    int v;
    const char* tag;
};

// 任务执行体
void myJob(Payload* p)
{
    if (!p)
        return;
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::cout << "[" << p->tag << "] job " << p->v << " done" << std::endl;
}

// 取消回调体
void myCancel(Payload* p)
{
    if (!p)
        return;
    std::cout << "[" << p->tag << "] Job " << p->v << " cancelled." << std::endl;
}

int main()
{
    auto threadPool = std::make_unique<ThreadManager>("MainThreadPool", 4);
    threadPool->SetQueueCap(8);

    // ---- 家族 A（有序）----
    ThreadManager::Handle hA = 0;
    threadPool->RegisterJobFamily("family-A", &hA, /*addInOrder*/ true, /*maxWindow*/ 8);

    std::vector<int> order = { 2, 0, 1, 5, 4, 3 };
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

    std::cout << "[A] All jobs posted. Waiting for sync..." << std::endl;
    threadPool->Sync(hA);
    std::cout << "[A] sync done" << std::endl;
    threadPool->PrintStats(hA); // [教学增强] 打印统计信息

    // 演示 Flush
    {
        auto p6 = std::make_shared<Payload>(6, "A");
        auto p7 = std::make_shared<Payload>(7, "A");
        threadPool->PostJob(hA, [p6]() { myJob(p6.get()); }, 6, ThreadManager::Priority::Default, {}, [p6]() { myCancel(p6.get()); });
        threadPool->PostJob(hA, [p7]() { myJob(p7.get()); }, 7, ThreadManager::Priority::Default, {}, [p7]() { myCancel(p7.get()); });
    }
    threadPool->Flush(hA);
    std::cout << "[A] flush done" << std::endl;
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
    std::cout << "\n[B] Trying SyncFor with a short timeout (will likely fail)..." << std::endl;
    bool success = threadPool->SyncFor(hB, std::chrono::milliseconds(10));
    std::cout << "[B] SyncFor " << (success ? "succeeded" : "timed out") << std::endl;

    std::cout << "[B] Waiting for final sync..." << std::endl;
    threadPool->Sync(hB);
    std::cout << "[B] sync done (cap/priority/deadline demo)" << std::endl;
    threadPool->PrintStats(hB);

    std::cout << "\nThread pool will be destroyed automatically by unique_ptr." << std::endl;

    return 0;
}