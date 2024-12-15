#include <atomic>
#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

// 假设主线程和子线程访问一个临界资源，主线程访问时，子线程不能访问，反之亦然
// 争夺的的大概就是enable标志位
static std::mutex m;
static std::atomic<bool> is_block;

auto func(const size_t& times, const std::string& name) -> void
{
    for (size_t i = 0; i < 50; ++i) {
        const auto start = std::chrono::high_resolution_clock::now();

        const auto end = std::chrono::high_resolution_clock::now();
        const std::chrono::duration<double, std::milli> elapsed = end - start;
        std::cout << "cost time " << elapsed << "." << std::endl;
    }
    while (true) {
        m.lock();
        for (size_t i = 0; i < times; ++i) {
            std::cout << __PRETTY_FUNCTION__ << " " << name << ": " << std::endl;
        }
        m.unlock();
        std::this_thread::yield();
    }
}

#if 0
子线程循环 10 次，接着主线程循环 100 次，接着又回到子线程循环 10 次，接着再回到主线程又循环 100 次，如此循环50次，试写出代码
#endif

auto main(int argc, char* argv[]) -> int
{
    std::thread child(func, 10, std::string("child"));
    child.join();
    func(100, std::string("main"));

    return 0;
}