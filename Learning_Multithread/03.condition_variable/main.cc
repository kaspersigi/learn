#include "ftrace.h"
#include <condition_variable>
#include <mutex>
#include <print>
#include <thread>

static std::mutex mutex;
static std::condition_variable cv;
static int i = 0;

void func1()
{
    Ftrace::trace_dur_begin("ChildThread1");
    while (i < 100) {
        std::unique_lock<std::mutex> ul(mutex);
        cv.wait(ul, []() { return 0 == i % 2; });
        std::print("a");
        i++;
        ul.unlock();
        cv.notify_one();
    }
    Ftrace::trace_dur_end();
}

void func2()
{
    Ftrace::trace_dur_begin("ChildThread2");
    while (i < 100) {
        std::unique_lock<std::mutex> ul(mutex);
        cv.wait(ul, []() { return 1 == i % 2; });
        std::print("b");
        i++;
        ul.unlock();
        cv.notify_one();
    }
    Ftrace::trace_dur_end();
}

auto main(int argc, char* argv[]) -> int
{
    Ftrace::trace_dur_begin("MainThread");
    std::thread t1(func1);
    std::thread t2(func2);
    t1.join();
    t2.join();
    Ftrace::trace_dur_end();

    return 0;
}