// ============================
// file: main.cc（演示）
// 适配改造点：
// 1) 使用 ThreadManager::DeleteAs<T>() 作为 cancel 回调，避免手写 delete；
// 2) 增加 family-B（无序），演示 Priority::High 的插队效果；
// 3) 演示队列上限触发的取消（cap 很小便于观测）；
// 4) 演示 deadline 过期取消；
// 5) 保留你原先的有序 family-A 流程与 Flush/Sync 语义。
// ============================
#include "threadmanager.h"
#include <chrono>
#include <print>
#include <thread>

// 简单负载：携带一个数值和标签（家族标识）
struct Payload {
    int v;
    const char* tag;
};

// 正常执行：打印并释放资源（仅用于“已执行”的任务）
static void myJob(void* p)
{
    auto* pl = static_cast<Payload*>(p);
    // 模拟工作
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::println("[{}] job {} done", pl->tag, pl->v);
    delete pl; // 注意：这里只释放“已执行”的；被取消的由 cancel 回调释放
}

int main()
{
    ThreadManager tm(4);

    // 为了更容易观察“队列上限触发取消”，先把 cap 设置得很小。
    // （若不需要该演示，改回较大值即可）
    tm.SetQueueCap(8);

    // ---- 家族 A：有序（ordered），带乱序窗口限制与 cancel 回调 ----
    ThreadManager::Handle hA = 0;
    tm.RegisterJobFamily(
        &myJob,
        "family-A",
        &hA,
        /*addInOrder*/ true,
        /*maxWindow*/ 8,
        /*cancel*/ ThreadManager::DeleteAs<Payload>() // 被取消时释放 Payload*
    );

    // 乱序提交（0..5 的顺序被打乱），有序家族会按 0,1,2,3,4,5 执行
    tm.PostJob(hA, new Payload { 2, "A" }, /*seq*/ 2);
    tm.PostJob(hA, new Payload { 0, "A" }, /*seq*/ 0);
    tm.PostJob(hA, new Payload { 1, "A" }, /*seq*/ 1);
    tm.PostJob(hA, new Payload { 5, "A" }, /*seq*/ 5);
    tm.PostJob(hA, new Payload { 4, "A" }, /*seq*/ 4);
    tm.PostJob(hA, new Payload { 3, "A" }, /*seq*/ 3);

    tm.Sync(hA);
    std::println("[A] sync done");

    // 演示 Flush：先投几条，再立刻 Flush（未开始的将被取消）
    tm.PostJob(hA, new Payload { 6, "A" }, 6);
    tm.PostJob(hA, new Payload { 7, "A" }, 7);
    tm.Flush(hA);
    std::println("[A] flush done");

    // ---- 家族 B：无序（unordered），用来演示优先级、队列上限与 deadline ----
    ThreadManager::Handle hB = 0;
    tm.RegisterJobFamily(
        &myJob,
        "family-B",
        &hB,
        /*addInOrder*/ false,
        /*maxWindow*/ 0,
        /*cancel*/ ThreadManager::DeleteAs<Payload>());

    // 先塞几条默认优先级任务
    for (int i = 100; i < 104; ++i) {
        tm.PostJob(hB, new Payload { i, "B" }, /*seq*/ 0, ThreadManager::Priority::Default);
    }

    // 再塞一条 High 优先级任务（应更快被执行）
    tm.PostJob(hB, new Payload { 999, "B-HIGH" }, /*seq*/ 0, ThreadManager::Priority::High);

    // 演示 deadline：给一个“已过期”的任务，应该被立即取消
    auto past = std::chrono::steady_clock::now() - std::chrono::milliseconds(1);
    tm.PostJob(hB, new Payload { 555, "B-EXP" }, /*seq*/ 0, ThreadManager::Priority::Default, past);

    // 演示队列上限：一次性投很多条，超过 cap 的会被拒绝并触发 cancel
    for (int i = 200; i < 220; ++i) {
        tm.PostJob(hB, new Payload { i, "B" }, /*seq*/ 0, ThreadManager::Priority::Default);
    }

    tm.Sync(hB);
    std::println("[B] sync done (cap/priority/deadline demo)");

    // 程序结束时，析构会做“软 Flush”，如仍有残留 pending/queued，会被 cancel 回收
    return 0;
}