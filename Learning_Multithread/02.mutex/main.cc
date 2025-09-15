#include "ftrace.h"
#include <iostream>
#include <mutex>
#include <thread>

std::mutex mtx;
int i = 0;

void print_a()
{
    Ftrace::ftrace_duration_begin("ChildThread1");
    while (true) {
        std::lock_guard<std::mutex> lock(mtx);
        if (i >= 100)
            break;
        if (i % 2 == 0) {
            std::cout << 'a' << std::flush;
            ++i;
        }
        // 不需要 else + yield —— 出临界区后自然重新竞争
    }
    Ftrace::ftrace_duration_end();
}

void print_b()
{
    Ftrace::ftrace_duration_begin("ChildThread2");
    while (true) {
        std::lock_guard<std::mutex> lock(mtx);
        if (i >= 100)
            break;
        if (i % 2 == 1) {
            std::cout << 'b' << std::flush;
            ++i;
        }
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
    std::cout << "\n✅ 互斥量版：打印完成！" << std::endl;
    Ftrace::ftrace_duration_end();

    return 0;
}