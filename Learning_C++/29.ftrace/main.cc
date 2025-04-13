#include "ftrace.h"
#include <chrono>
#include <thread>

void func_dur(int num)
{
    Ftrace::ftrace_duration_begin("FuncDur");
    for (size_t i = 0; i < num; ++i) {
        std::string str = std::format("Duration{}", i);
        Ftrace::ftrace_duration_begin(str);
        std::this_thread::sleep_for(std::chrono::milliseconds(90));
        Ftrace::ftrace_duration_end();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    Ftrace::ftrace_duration_end();
}

void func_cnt1(int num)
{
    Ftrace::ftrace_duration_begin("FuncCnt1");
    Ftrace::ftrace_instant("lzz said something");
    for (size_t i = 0; i < num; ++i) {
        std::string str("Count1");
        Ftrace::ftrace_counter_set(str, i);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        Ftrace::ftrace_counter_zero(str);
        std::this_thread::sleep_for(std::chrono::milliseconds(90));
    }
    Ftrace::ftrace_duration_end();
}

void func_cnt2(int num)
{
    Ftrace::ftrace_duration_begin("FuncCnt2");
    Ftrace::ftrace_instant("lzz don't say anything");
    for (size_t i = 0; i < num; ++i) {
        std::string str("Count2");
        Ftrace::ftrace_counter_set(str, i * 2);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        Ftrace::ftrace_counter_set(str, i * 2 + 1);
        std::this_thread::sleep_for(std::chrono::milliseconds(90));
    }
    Ftrace::ftrace_duration_end();
}

auto main(int argc, char* argv[]) -> int
{
    Ftrace::ftrace_duration_begin("MainThread");
    std::thread dur(func_dur, 50);
    std::thread cnt1(func_cnt1, 50);
    std::thread cnt2(func_cnt2, 50);
    dur.join();
    cnt1.join();
    cnt2.join();
    Ftrace::ftrace_duration_end();

    return 0;
}