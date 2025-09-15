#if 0
#include "ftrace.h"
#include <atomic>
#include <iostream>
#include <thread>

std::atomic<int> i { 0 }; // 当前打印次数

void print_a()
{
    Ftrace::ftrace_duration_begin("ChildThread1");
    while (true) {
        int current = i.load(std::memory_order_acquire);
        if (current >= 100)
            break;

        if (current % 2 == 0) {
            std::cout << 'a' << std::flush;
            i.fetch_add(1, std::memory_order_release);
        } else {
            std::this_thread::yield(); // 礼让，减少CPU空转
        }
    }
    Ftrace::ftrace_duration_end();
}

void print_b()
{
    Ftrace::ftrace_duration_begin("ChildThread2");
    while (true) {
        int current = i.load(std::memory_order_acquire);
        if (current >= 100)
            break;

        if (current % 2 == 1) {
            std::cout << 'b' << std::flush;
            i.fetch_add(1, std::memory_order_release);
        } else {
            std::this_thread::yield();
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
    std::cout << "\n✅ 原子变量版：打印完成！" << std::endl;
    Ftrace::ftrace_duration_end();

    return 0;
}
#else
#include "ftrace.h"
#include <atomic>
#include <iostream>
#include <thread>

std::atomic<int> i { 0 };

void print_a()
{
    Ftrace::ftrace_duration_begin("ChildThread1");
    while (true) {
        int current = i.load(std::memory_order_acquire);
        if (current >= 100)
            break;

        if (current % 2 == 0) {
            std::cout << 'a' << std::flush;
            i.fetch_add(1, std::memory_order_release);
            i.notify_one(); // 唤醒等待者
        } else {
            i.wait(current); // 阻塞直到 i 改变
        }
    }
    Ftrace::ftrace_duration_end();
}

void print_b()
{
    Ftrace::ftrace_duration_begin("ChildThread2");
    while (true) {
        int current = i.load(std::memory_order_acquire);
        if (current >= 100)
            break;

        if (current % 2 == 1) {
            std::cout << 'b' << std::flush;
            i.fetch_add(1, std::memory_order_release);
            i.notify_one();
        } else {
            i.wait(current);
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
    std::cout << "\n✅ C++20 原子 wait/notify 版：打印完成！" << std::endl;
    Ftrace::ftrace_duration_end();

    return 0;
}
#endif