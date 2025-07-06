#include "ftrace.h"
#include "threadpool.hpp"
#include <chrono>
#include <cmath>
#include <condition_variable>
#include <cstddef>
#include <mutex>
#include <string>
#include <thread>

const size_t frame_rate = 30;
const size_t max_hal_request = 6;
const size_t max_frames = 100;

const size_t bufferQ = 5;
size_t consumerQ = 0;
std::mutex mtx_bufferQ;
std::condition_variable cv_consumer;

std::atomic<size_t> vsync_id(0);
std::atomic<size_t> wait_id(0);
std::mutex mtx_vsync;
std::condition_variable cv_vsync;

ThreadPool halpool(max_hal_request);
ThreadPool framworkpool(bufferQ);

size_t ms2ns(double milliseconds)
{
    return std::llround(milliseconds * 1000000);
}

void threeA(size_t frame_number)
{
    std::string str("3A:");
    Ftrace::ftrace_duration_begin(str + std::to_string(frame_number));
    std::this_thread::sleep_for(std::chrono::milliseconds(15));
    Ftrace::ftrace_duration_end();
}

void exposure(size_t frame_number)
{
    std::string str("Exp:");
    Ftrace::ftrace_duration_begin(str + std::to_string(frame_number));
    std::this_thread::sleep_for(std::chrono::milliseconds(8));
    Ftrace::ftrace_duration_end();
}

void readout(size_t frame_number)
{
    std::string str("Readout:");
    Ftrace::ftrace_duration_begin(str + std::to_string(frame_number));
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    Ftrace::ftrace_duration_end();
}

void sof(size_t frame_number)
{
    std::string str("SOF:");
    Ftrace::ftrace_duration_begin(str + std::to_string(frame_number));
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    Ftrace::ftrace_duration_end();
}

void sensor(size_t frame_number, size_t id)
{
    std::string str("Sensor:");
    Ftrace::ftrace_duration_begin(str + std::to_string(frame_number));
    std::unique_lock<std::mutex> ul(mtx_vsync);
    cv_vsync.wait(ul, [=]() { return id == vsync_id; });
    exposure(frame_number);
    readout(frame_number);
    Ftrace::ftrace_duration_end();
}

void ife(size_t frame_number)
{
    std::string str("IFE:");
    Ftrace::ftrace_duration_begin(str + std::to_string(frame_number));
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    Ftrace::ftrace_duration_end();
}

void realtime(size_t frame_number)
{
    std::string str("realtime:");
    Ftrace::ftrace_duration_begin(str + std::to_string(frame_number));
    threeA(frame_number);
    size_t expose_id = 0;
    if (wait_id <= vsync_id) {
        expose_id = vsync_id + 1;
        wait_id = expose_id;
    } else {
        expose_id = wait_id + 1;
        wait_id.fetch_add(1);
    }
    Ftrace::ftrace_instant("expose vsync: " + std::to_string(expose_id));
    sensor(frame_number, expose_id);
    sof(frame_number);
    ife(frame_number);
    Ftrace::ftrace_duration_end();
}

void offline(size_t frame_number)
{
    std::string str("offline:");
    Ftrace::ftrace_duration_begin(str + std::to_string(frame_number));
    std::this_thread::sleep_for(std::chrono::milliseconds(45));
    Ftrace::ftrace_duration_end();
}

void vsync(double fps, double offset)
{
    size_t interval = ms2ns(1000.0 / fps);
    std::this_thread::sleep_for(std::chrono::nanoseconds(ms2ns(offset)));
    while (true) {
        Ftrace::ftrace_counter_set("Vsync", 1);
        vsync_id.fetch_add(1);
        cv_vsync.notify_all();
        Ftrace::ftrace_counter_set("Vsync id", vsync_id);
        Ftrace::ftrace_counter_zero("Vsync id");
        Ftrace::ftrace_counter_zero("Vsync");
        std::this_thread::sleep_for(std::chrono::nanoseconds(interval));
    }
}

void process_capture_request(size_t frame_number)
{
    Ftrace::ftrace_async_start("HAL3: RequestTrace", std::to_string(frame_number));
    realtime(frame_number);
    offline(frame_number);
    {
        std::lock_guard<std::mutex> lk(mtx_bufferQ);
        consumerQ--;
        cv_consumer.notify_all();
    }
    Ftrace::ftrace_async_end("HAL3: RequestTrace", std::to_string(frame_number));
}

void frame_capture(size_t frame_number)
{
    Ftrace::ftrace_async_start("frame capture", std::to_string(frame_number));
    auto future = halpool.enqueue(process_capture_request, frame_number);
    future.get();
    Ftrace::ftrace_async_end("frame capture", std::to_string(frame_number));
}

void threadloop()
{
    size_t frame_number = 0;
    while (frame_number <= max_frames) {
        {
            std::unique_lock<std::mutex> ul(mtx_bufferQ);
            cv_consumer.wait(ul, []() { return consumerQ < bufferQ; });
            consumerQ++;
            Ftrace::ftrace_duration_end();
            Ftrace::ftrace_duration_begin("threadloop");
            framworkpool.enqueue(frame_capture, frame_number);
            frame_number++;
            cv_consumer.notify_all();
        }
    }
    Ftrace::ftrace_duration_end();
}

auto main(int argc, char* argv[]) -> int
{
    Ftrace::ftrace_duration_begin("MainThread");
    std::thread v(vsync, frame_rate, 22);
    v.detach();
    std::thread t(threadloop);
    t.join();
    Ftrace::ftrace_duration_end();
    Ftrace::ftrace_duration_begin("WaitForExit");
    std::this_thread::sleep_for(std::chrono::seconds(1));
    Ftrace::ftrace_duration_end();

    return 0;
}