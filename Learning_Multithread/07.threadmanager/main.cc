// ============================
// file: main.cc（演示）
// 说明：展示家族注册、按序与无序投递、队列上限、优先级插队、过期任务与 Flush/Sync 的行为
// 注意：示例仅演示用法；回调里 delete “已执行任务”的数据；被取消的任务由 cancel 回调回收
// ============================

#include "threadmanager.h"
#include <chrono>
#include <print>
#include <thread>

// 演示用负载：携带一个整数与家族标签
struct Payload {
    int v;
    const char* tag;
};

// 执行体：模拟工作并打印；仅对“已执行”的任务释放资源
auto myJob(void* p) -> void
{
    auto* pl = static_cast<Payload*>(p);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::println("[{}] job {} done", pl->tag, pl->v);
    delete pl; // 被取消的任务资源由 cancel 回调释放
}

auto main(int argc, char* argv[]) -> int
{
    // 创建 4 个 worker
    ThreadManager* pPerfThreadPool = nullptr;
    bool ret = ThreadManager::Create(&pPerfThreadPool, "PerfThreadManager", 4);

    // 为了更直观看到“队列上限触发取消”，将 cap 设置较小
    pPerfThreadPool->SetQueueCap(8);

    // ---- 家族 A（有序）----
    // - 开启 addInOrder，使用乱序窗口 8
    // - 注册取消回调用于回收被拒/过期/Flush 的 Payload*
    ThreadManager::Handle hA = 0;
    pPerfThreadPool->RegisterJobFamily(
        &myJob,
        "family-A",
        &hA,
        /*addInOrder*/ true,
        /*maxWindow*/ 8,
        /*cancel*/ ThreadManager::DeleteAs<Payload>());

    // 乱序提交 0..5；实际执行顺序应为 0,1,2,3,4,5
    pPerfThreadPool->PostJob(hA, new Payload { 2, "A" }, /*seq*/ 2);
    pPerfThreadPool->PostJob(hA, new Payload { 0, "A" }, /*seq*/ 0);
    pPerfThreadPool->PostJob(hA, new Payload { 1, "A" }, /*seq*/ 1);
    pPerfThreadPool->PostJob(hA, new Payload { 5, "A" }, /*seq*/ 5);
    pPerfThreadPool->PostJob(hA, new Payload { 4, "A" }, /*seq*/ 4);
    pPerfThreadPool->PostJob(hA, new Payload { 3, "A" }, /*seq*/ 3);

    // 等待家族 A 清空
    pPerfThreadPool->Sync(hA);
    std::println("[A] sync done");

    // 演示 Flush：提交 6、7 后立即 Flush，未执行的会被取消
    pPerfThreadPool->PostJob(hA, new Payload { 6, "A" }, 6);
    pPerfThreadPool->PostJob(hA, new Payload { 7, "A" }, 7);
    pPerfThreadPool->Flush(hA);
    std::println("[A] flush done");

    // ---- 家族 B（无序）----
    // - 用于演示优先级、队列上限与 deadline 行为
    ThreadManager::Handle hB = 0;
    pPerfThreadPool->RegisterJobFamily(
        &myJob,
        "family-B",
        &hB,
        /*addInOrder*/ false,
        /*maxWindow*/ 0,
        /*cancel*/ ThreadManager::DeleteAs<Payload>());

    // 提交数条默认优先级任务
    for (int i = 100; i < 104; ++i) {
        pPerfThreadPool->PostJob(hB, new Payload { i, "B" }, /*seq*/ 0, ThreadManager::Priority::Default);
    }

    // 提交一条高优先级任务（应更早被执行）
    pPerfThreadPool->PostJob(hB, new Payload { 999, "B-HIGH" }, /*seq*/ 0, ThreadManager::Priority::High);

    // 演示过期：给一个已经过期的 deadline，任务会被直接取消
    auto past = std::chrono::steady_clock::now() - std::chrono::milliseconds(1);
    pPerfThreadPool->PostJob(hB, new Payload { 555, "B-EXP" }, /*seq*/ 0, ThreadManager::Priority::Default, past);

    // 演示队列上限：一次性投很多条，超过 cap 的会被拒并触发取消回调
    for (int i = 200; i < 220; ++i) {
        pPerfThreadPool->PostJob(hB, new Payload { i, "B" }, /*seq*/ 0, ThreadManager::Priority::Default);
    }

    // 等待家族 B 清空
    pPerfThreadPool->Sync(hB);
    std::println("[B] sync done (cap/priority/deadline demo)");

    // 程序结束：析构将执行“软 Flush”，确保资源被取消回调回收
    pPerfThreadPool->Destroy();
    pPerfThreadPool = nullptr;

    return 0;
}