#include "ftrace.h"
#include <chrono>
#include <cmath>
#include <string>
#include <thread>

long long ms2ns(double milliseconds)
{
    return std::llround(milliseconds * 1000000);
}

void vsync(double fps, double offset)
{
    long long interval = ms2ns(1000.0 / fps);
    std::this_thread::sleep_for(std::chrono::nanoseconds(ms2ns(offset)));
    while (true) {
        Ftrace::ftrace_counter_set("Vsync", 1);
        Ftrace::ftrace_counter_zero("Vsync");
        std::this_thread::sleep_for(std::chrono::nanoseconds(interval));
    }
}

void frame_capture(double delay)
{
    long long interval = ms2ns(delay);
    size_t count = 0;
    while (true) {
        Ftrace::ftrace_async_begin("frame capture", std::to_string(count));
        std::this_thread::sleep_for(std::chrono::nanoseconds(interval));
        Ftrace::ftrace_async_end("frame capture", std::to_string(count));
        ++count;
    }
}

auto main(int argc, char* argv[]) -> int
{
    Ftrace::ftrace_duration_begin("MainThread");
    std::thread v(vsync, 30, 10);
    v.detach();
    std::thread f(frame_capture, 10);
    f.detach();
    std::this_thread::sleep_for(std::chrono::seconds(5));
    Ftrace::ftrace_duration_end();

    return 0;
}