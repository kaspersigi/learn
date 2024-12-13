#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

static bool child_enable = true;
std::condition_variable cv_m;
std::condition_variable cv_c;

void main_thread()
{
    // while (true) {
    std::cout << std::endl;
    for (size_t i = 0; i < 100; ++i)
        std::cout << 'a' << std::flush;
    // }
}

void child_thread()
{
    // while (true) {
    std::cout << std::endl;
    for (size_t i = 0; i < 10; ++i)
        std::cout << 'b' << std::flush;
    // }
}

#if 0
子线程循环 10 次，接着主线程循环 100 次，接着又回到子线程循环 10 次，接着再回到主线程又循环 100 次，如此循环50次，试写出代码
#endif

auto main(int argc, char* argv[]) -> int
{
    // std::thread c(child_thread);
    // std::thread m(main_thread);
    // c.join();
    // m.join();
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    return 0;
}