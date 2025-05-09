#include "ftrace.h"
#include <condition_variable>
#include <mutex>
#include <print>
#include <thread>

// 最好改成回调，当callback为ok时，继续执行，否则阻塞至ok

class Singleton {
public:
    ~Singleton() = default;
    static Singleton& GetInstance();

protected:
    Singleton() = default;
    Singleton(const Singleton& obj) = delete;
    Singleton(Singleton&& obj) = delete;
    Singleton& operator=(const Singleton& obj) = delete;
    Singleton& operator=(Singleton&& obj) = delete;

private:
    std::mutex _mutex;
    std::condition_variable _cv;
    bool is_finish { false };

public:
    void notify();
    void wait();
    void doing();
};

Singleton& Singleton::GetInstance()
{
    static Singleton instance;
    return instance;
}

void Singleton::notify()
{
    _cv.notify_one();
}

void Singleton::wait()
{
    std::unique_lock<std::mutex> ul(_mutex);
    _cv.wait(ul, [this]() { return is_finish; });
}

void Singleton::doing()
{
    std::println("{}: process E", __func__);
    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::println("{}: process X", __func__);
    {
        std::lock_guard<std::mutex> lg(_mutex);
        is_finish = true;
    }
}

void func1()
{
    Ftrace::ftrace_duration_begin("ChildThread1");
    std::println("{}: process E", __func__);
    auto& s = Singleton::GetInstance();
    s.doing();
    s.notify();
    std::println("{}: process X", __func__);
    Ftrace::ftrace_duration_end();
}

void func2()
{
    Ftrace::ftrace_duration_begin("ChildThread2");
    std::println("{}: process E", __func__);
    auto& s = Singleton::GetInstance();
    s.wait();
    std::println("{}: process X", __func__);
    Ftrace::ftrace_duration_end();
}

auto main(int argc, char* argv[]) -> int
{
    Ftrace::ftrace_duration_begin("MainThread");
    std::println("{}: process E", __func__);
    std::thread t1(func1);
    std::thread t2(func2);
    t1.detach();
    t2.join();
    std::println("{}: process X", __func__);
    Ftrace::ftrace_duration_end();

    return 0;
}