// ============================
// file: main.cc（演示）
// 说明：展示 AdvanceThreadManager 的现代化用法
// ============================

#include "advancethreadmanager.h"
#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

// 演示用负载：携带一个整数与家族标签
struct Payload {
    int v;
    const char* tag;
};

// 执行体：现在接收 Payload*
void myJob(Payload* pl)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::cout << "[" << pl->tag << "] job " << pl->v << " done" << std::endl;
}

int main(int argc, char* argv[])
{
    // 1. RAII: 使用 unique_ptr 管理线程池生命周期
    auto threadPool = std::make_unique<AdvanceThreadManager>("PerfThreadPool", 4);

    // 为了更直观看到“队列上限触发取消”，将 cap 设置较小
    threadPool->SetQueueCap(8);

    // ---- 家族 A（有序）----
    AdvanceThreadManager::Handle hA = 0;
    threadPool->RegisterJobFamily("family-A", &hA, /*addInOrder*/ true, /*maxWindow*/ 8);

    // 2. 类型安全: 使用 lambda 提交任务，通过共享指针管理负载生命周期
    auto postOrderedJob = [&](int val, int seq) {
        // 使用 std::shared_ptr，它可以被安全地复制到多个 lambda 中
        auto p = std::make_shared<Payload>(Payload { val, "A" });

        threadPool->PostJob(
            hA,
            // 按值捕获 p (复制 shared_ptr，增加引用计数)
            [p]() { myJob(p.get()); },
            seq,
            AdvanceThreadManager::Priority::Default,
            {},
            // 取消回调也按值捕获同一个 shared_ptr
            [p]() {
                std::cout << "[A] Job " << p->v << " cancelled." << std::endl;
            });
    };

    // 乱序提交 0..5；执行应严格按 0,1,2,3,4,5 顺序
    postOrderedJob(2, 2);
    postOrderedJob(0, 0);
    postOrderedJob(1, 1);
    postOrderedJob(5, 5);
    postOrderedJob(4, 4);
    postOrderedJob(3, 3);

    threadPool->Sync(hA);
    std::cout << "[A] sync done" << std::endl;

    // 演示 Flush
    postOrderedJob(6, 6);
    postOrderedJob(7, 7);
    threadPool->Flush(hA);
    std::cout << "[A] flush done" << std::endl;

    // ---- 家族 B（无序）----
    AdvanceThreadManager::Handle hB = 0;
    threadPool->RegisterJobFamily("family-B", &hB);

    auto postUnorderedJob = [&](int val, const char* tag, AdvanceThreadManager::Priority prio = AdvanceThreadManager::Priority::Default, std::chrono::steady_clock::time_point deadline = {}) {
        // 同样使用 std::shared_ptr
        auto p = std::make_shared<Payload>(Payload { val, tag });
        threadPool->PostJob(
            hB,
            [p]() { myJob(p.get()); },
            0,
            prio,
            deadline,
            [p]() {
                std::cout << "[" << p->tag << "] Job " << p->v << " cancelled." << std::endl;
            });
    };

    // 提交数条默认优先级任务
    for (int i = 100; i < 104; ++i) {
        postUnorderedJob(i, "B");
    }

    // 提交一条高优先级任务
    postUnorderedJob(999, "B-HIGH", AdvanceThreadManager::Priority::High);

    // 演示过期
    auto past = std::chrono::steady_clock::now() - std::chrono::milliseconds(1);
    postUnorderedJob(555, "B-EXP", AdvanceThreadManager::Priority::Default, past);

    // 演示队列上限
    for (int i = 200; i < 220; ++i) {
        postUnorderedJob(i, "B");
    }

    threadPool->Sync(hB);
    std::cout << "[B] sync done (cap/priority/deadline demo)" << std::endl;

    // 3. 自动清理: unique_ptr 离开作用域，线程池自动析构，无需手动 Destroy()
    return 0;
}