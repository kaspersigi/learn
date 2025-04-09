#include <condition_variable>
#include <mutex>
#include <print>
#include <thread>

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
    std::println("{}: process E", __func__);
    _cv.notify_one();
    std::println("{}: process X", __func__);
}

void Singleton::wait()
{
    std::println("{}: process E", __func__);
    std::unique_lock<std::mutex> ul(_mutex);
    _cv.wait(ul, [this]() { return is_finish; });
    std::println("{}: process X", __func__);
}

void Singleton::doing()
{
    std::println("{}: process E", __func__);
    std::this_thread::sleep_for(std::chrono::seconds(5));
    _mutex.lock();
    is_finish = true;
    _mutex.unlock();
    std::println("{}: process X", __func__);
}

void func1()
{
    std::println("{}: process E", __func__);
    auto& s = Singleton::GetInstance();
    s.doing();
    s.notify();
    std::println("{}: process X", __func__);
}

void func2()
{
    std::println("{}: process E", __func__);
    auto& s = Singleton::GetInstance();
    s.wait();
    std::println("{}: process X", __func__);
}

auto main(int argc, char* argv[]) -> int
{
    std::println("{}: process E", __func__);
    std::thread t1(func1);
    std::thread t2(func2);
    t1.detach();
    t2.join();
    std::println("{}: process X", __func__);

    return 0;
}