// ============================
// file: main.cc（演示）
// ============================
#include "threadmanager.h"
#include <chrono>
#include <print>
#include <thread>

static void myJob(void* p)
{
    int* pi = static_cast<int*>(p);
    int v = *pi;
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::println("job {} done", v);
    delete pi;
}

static void myCancel(void* p)
{
    int* pi = static_cast<int*>(p);
    std::println("job {} canceled", *pi);
    delete pi;
}

int main()
{
    ThreadManager tm(4);
    tm.SetQueueCap(1024);

    ThreadManager::Handle hf = 0;
    tm.RegisterJobFamily(&myJob, "family-A", &hf, /*addInOrder*/ true, /*maxWindow*/ 8, /*cancel*/ &myCancel);

    // 乱序提交（0..9 的顺序被打乱），有序家族会按 0,1,2,... 执行
    tm.PostJob(hf, new int(2), 2);
    tm.PostJob(hf, new int(0), 0);
    tm.PostJob(hf, new int(1), 1);
    tm.PostJob(hf, new int(5), 5);
    tm.PostJob(hf, new int(4), 4);
    tm.PostJob(hf, new int(3), 3);

    tm.Sync(hf);
    std::println("sync done");

    // 演示 Flush：先投几条，再立刻 Flush
    tm.PostJob(hf, new int(6), 6);
    tm.PostJob(hf, new int(7), 7);
    tm.Flush(hf);
    std::println("flush done");

    return 0;
}