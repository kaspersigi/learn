#include "ftrace.h"
#include "threadpool.hpp"
#include <chrono>
#include <cmath>
#include <string>
#include <thread>

std::atomic<size_t> vsync_id(0);

long long ms2ns(double milliseconds)
{
    return std::llround(milliseconds * 1000000);
}

void threeA(size_t req)
{
    std::string str("3A:");
    Ftrace::ftrace_duration_begin(str + std::to_string(req));
    std::this_thread::sleep_for(std::chrono::milliseconds(30));
    Ftrace::ftrace_duration_end();
}

void tfe(size_t req)
{
    std::string str("tfe:");
    Ftrace::ftrace_duration_begin(str + std::to_string(req));
    std::this_thread::sleep_for(std::chrono::milliseconds(70));
    Ftrace::ftrace_duration_end();
}

void offline(size_t req)
{
    std::string str("offline:");
    Ftrace::ftrace_duration_begin(str + std::to_string(req));
    std::this_thread::sleep_for(std::chrono::milliseconds(60));
    Ftrace::ftrace_duration_end();
}

void vsync(double fps, double offset)
{
    long long interval = ms2ns(1000.0 / fps);
    std::this_thread::sleep_for(std::chrono::nanoseconds(ms2ns(offset)));
    while (true) {
        Ftrace::ftrace_counter_set("Vsync", 1);
        vsync_id.fetch_add(1);
        Ftrace::ftrace_counter_zero("Vsync");
        std::this_thread::sleep_for(std::chrono::nanoseconds(interval));
    }
}

void frame_capture(size_t req)
{
    Ftrace::ftrace_async_begin("frame capture", std::to_string(req));
    threeA(req);
    tfe(req);
    offline(req);
    Ftrace::ftrace_async_end("frame capture", std::to_string(req));
}

void thread_loop(size_t threads, double delay)
{
    ThreadPool pool(6);
    long long interval = ms2ns(delay);
    size_t req = 0;
    while (true) {
        auto future = pool.enqueue(frame_capture, req);
        std::this_thread::sleep_for(std::chrono::nanoseconds(interval));
        ++req;
    }
}

auto main(int argc, char* argv[]) -> int
{
    Ftrace::ftrace_duration_begin("MainThread");
    std::thread v(vsync, 30, 10);
    v.detach();
    std::thread l(thread_loop, 6, 10);
    l.detach();
    std::this_thread::sleep_for(std::chrono::seconds(5));
    Ftrace::ftrace_duration_end();

    return 0;
}