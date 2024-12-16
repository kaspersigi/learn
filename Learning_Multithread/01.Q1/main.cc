#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>

#if 0
子线程循环 10 次，接着主线程循环 100 次，接着又回到子线程循环 10 次，接着再回到主线程又循环 100 次，如此循环50次，试写出代码
#endif

// 假设主线程和子线程访问一个临界资源，主线程访问时，子线程不能访问，反之亦然
// 争夺的的大概就是enable标志位

#if 0
static const size_t count = 50;
static std::atomic<size_t> flag = 10;

auto func(const size_t& times, const std::string& name) -> void
{
    for (size_t i = 0; i < count; ++i) {
        while (times != flag) {
            std::this_thread::yield();
        }
        const auto start = std::chrono::high_resolution_clock::now();
        for (size_t k = 0; k < times; ++k) {
            std::cout << __PRETTY_FUNCTION__ << " " << name << ": " << i + 1 << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
        const auto end = std::chrono::high_resolution_clock::now();
        const std::chrono::duration<double, std::milli> elapsed = end - start;
        std::cout << "cost time " << elapsed << "." << std::endl;
        flag = (flag == 10 ? 100 : 10);
    }
}
#else
#include <condition_variable>
#include <mutex>
static const size_t count = 50;
static std::condition_variable cv;
static std::atomic<size_t> flag = 10;
static std::mutex m;

auto func(const size_t& times, const std::string& name) -> void
{
    for (size_t i = 0; i < count; ++i) {
        std::unique_lock<std::mutex> lk(m);
        cv.wait(lk, [=]() { return flag == times; });
        const auto start = std::chrono::high_resolution_clock::now();
        for (size_t k = 0; k < times; ++k) {
            std::cout << __PRETTY_FUNCTION__ << " " << name << ": " << i + 1 << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
        const auto end = std::chrono::high_resolution_clock::now();
        const std::chrono::duration<double, std::milli> elapsed = end - start;
        std::cout << "cost time " << elapsed << "." << std::endl;
        flag = (flag == 10 ? 100 : 10);
        lk.unlock();
        cv.notify_one();
    }
}
#endif

auto main(int argc, char* argv[]) -> int
{
    std::thread child(func, 10, std::string("child"));
    func(100, std::string("main"));
    child.join();

    return 0;
}