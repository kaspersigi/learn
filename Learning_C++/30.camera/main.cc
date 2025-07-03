#include "ftrace.h"
#include "threadpool.hpp"
#include <chrono>
#include <cmath>
#include <condition_variable>
#include <cstddef>
#include <mutex>
#include <string>
#include <thread>

std::atomic<size_t> vsync_id(0);
std::atomic<size_t> wait_id(0);
std::mutex mtx;
std::condition_variable cv;

size_t ms2ns(double milliseconds)
{
    return std::llround(milliseconds * 1000000);
}

void threeA(size_t req)
{
    std::string str("3A:");
    Ftrace::ftrace_duration_begin(str + std::to_string(req));
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    Ftrace::ftrace_duration_end();
}

void exposure(size_t req)
{
    std::string str("Exp:");
    Ftrace::ftrace_duration_begin(str + std::to_string(req));
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    Ftrace::ftrace_duration_end();
}

void readout(size_t req)
{
    std::string str("Readout:");
    Ftrace::ftrace_duration_begin(str + std::to_string(req));
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    Ftrace::ftrace_duration_end();
}

void sof(size_t req)
{
    std::string str("SOF:");
    Ftrace::ftrace_duration_begin(str + std::to_string(req));
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    Ftrace::ftrace_duration_end();
}

void sensor(size_t req, size_t id)
{
    std::string str("Sensor:");
    Ftrace::ftrace_duration_begin(str + std::to_string(req));
    std::unique_lock<std::mutex> ul(mtx);
    cv.wait(ul, [=]() { return id == vsync_id; });
    exposure(req);
    readout(req);
    Ftrace::ftrace_duration_end();
}

void ife(size_t req)
{
    std::string str("IFE:");
    Ftrace::ftrace_duration_begin(str + std::to_string(req));
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    Ftrace::ftrace_duration_end();
}

void realtime(size_t req)
{
    std::string str("realtime:");
    Ftrace::ftrace_duration_begin(str + std::to_string(req));
    threeA(req);
    size_t expose_id = 0;
    if (wait_id <= vsync_id) {
        expose_id = vsync_id + 1;
        wait_id = expose_id;
    } else {
        expose_id = wait_id + 1;
        wait_id.fetch_add(1);
    }
    Ftrace::ftrace_instant("expose vsync: " + std::to_string(expose_id));
    sensor(req, expose_id);
    sof(req);
    ife(req);
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
    size_t interval = ms2ns(1000.0 / fps);
    std::this_thread::sleep_for(std::chrono::nanoseconds(ms2ns(offset)));
    while (true) {
        Ftrace::ftrace_counter_set("Vsync", 1);
        vsync_id.fetch_add(1);
        cv.notify_all();
        Ftrace::ftrace_counter_set("Vsync id", vsync_id);
        Ftrace::ftrace_counter_zero("Vsync id");
        Ftrace::ftrace_counter_zero("Vsync");
        std::this_thread::sleep_for(std::chrono::nanoseconds(interval));
    }
}

void frame_capture(size_t req)
{
    Ftrace::ftrace_async_start("frame capture", std::to_string(req));
    realtime(req);
    offline(req);
    Ftrace::ftrace_async_end("frame capture", std::to_string(req));
}

void thread_loop(size_t threads, double delay)
{
    ThreadPool pool(threads);
    size_t interval = ms2ns(delay);
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