#include <atomic>
#include <iostream>
#include <thread>

#if 0
编写一个程序，开启3个线程，这3个线程的ID分别为A、B、C，每个线程将自己的ID在屏幕上打印10遍，要求输出结果必须按ABC的顺序显示；如：ABCABC….依次递推
#endif

#if 0
static const size_t count = 10;
static std::atomic<size_t> flag = 0;

auto A() -> void
{
    for (size_t i = 0; i < count; ++i) {
        while (flag % 3 != 0) {
            std::this_thread::yield();
        }
        std::cout << 'A' << std::flush;
        flag++;
    }
}

auto B() -> void
{
    for (size_t i = 0; i < count; ++i) {
        while (flag % 3 != 1) {
            std::this_thread::yield();
        }
        std::cout << 'B' << std::flush;
        flag++;
    }
}

auto C() -> void
{
    for (size_t i = 0; i < count; ++i) {
        while (flag % 3 != 2) {
            std::this_thread::yield();
        }
        std::cout << 'C' << std::flush;
        flag++;
    }
}
#else
#include <condition_variable>
#include <mutex>

static const size_t count = 10;
static std::atomic<size_t> flag = 0;
static std::mutex m;
static std::condition_variable cv;

auto A() -> void
{
    for (size_t i = 0; i < count; ++i) {
        std::unique_lock<std::mutex> lk(m);
        cv.wait(lk, [=]() { return flag % 3 == 0; });
        std::cout << 'A' << std::flush;
        flag++;
        lk.unlock();
        cv.notify_all();
    }
}

auto B() -> void
{
    for (size_t i = 0; i < count; ++i) {
        std::unique_lock<std::mutex> lk(m);
        cv.wait(lk, [=]() { return flag % 3 == 1; });
        std::cout << 'B' << std::flush;
        flag++;
        lk.unlock();
        cv.notify_all();
    }
}

auto C() -> void
{
    for (size_t i = 0; i < count; ++i) {
        std::unique_lock<std::mutex> lk(m);
        cv.wait(lk, [=]() { return flag % 3 == 2; });
        std::cout << 'C' << std::flush;
        flag++;
        lk.unlock();
        cv.notify_all();
    }
}

#endif

auto main(int argc, char* argv[]) -> int
{
    std::thread a(A);
    std::thread b(B);
    std::thread c(C);
    a.join();
    b.join();
    c.join();

    return 0;
}