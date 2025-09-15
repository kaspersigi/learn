#include "ftrace.h"
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

std::mutex mtx;
std::condition_variable cv;
int i = 0;

void print_a()
{
    Ftrace::ftrace_duration_begin("ChildThread1");
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        // 等待：要么结束，要么轮到自己
        cv.wait(lock, [] { return i >= 100 || i % 2 == 0; });
        if (i >= 100)
            break;
        std::cout << 'a' << std::flush;
        ++i;
        cv.notify_one(); // 唤醒另一个线程
    }
    Ftrace::ftrace_duration_end();
}

void print_b()
{
    Ftrace::ftrace_duration_begin("ChildThread2");
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return i >= 100 || i % 2 == 1; });
        if (i >= 100)
            break;
        std::cout << 'b' << std::flush;
        ++i;
        cv.notify_one();
    }
    Ftrace::ftrace_duration_end();
}

int main(int argc, char* argv[])
{
    Ftrace::ftrace_duration_begin("MainThread");
    std::thread t1(print_a);
    std::thread t2(print_b);
    t1.join();
    t2.join();
    std::cout << "\n✅ 条件变量版：打印完成！" << std::endl;
    Ftrace::ftrace_duration_end();

    return 0;
}