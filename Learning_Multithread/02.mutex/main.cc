#include <mutex>
#include <print>
#include <thread>

static std::mutex mutex;
static int i = 0;

#if 0
void func1()
{
    while (i < 100) {
        if (0 == i % 2) {
            mutex.lock();
            std::print("a");
            i++;
            mutex.unlock();
        } else {
            std::this_thread::yield();
        }
    }
}

void func2()
{
    while (i < 100) {
        if (1 == i % 2) {
            mutex.lock();
            std::print("b");
            i++;
            mutex.unlock();
        } else {
            std::this_thread::yield();
        }
    }
}
#else
void func1()
{
    while (i < 100) {
        if (0 == i % 2) {
            std::lock_guard<std::mutex> lg(mutex);
            std::print("a");
            i++;
        } else {
            std::this_thread::yield();
        }
    }
}

void func2()
{
    while (i < 100) {
        if (1 == i % 2) {
            std::lock_guard<std::mutex> lg(mutex);
            std::print("b");
            i++;
        } else {
            std::this_thread::yield();
        }
    }
}
#endif

auto main(int argc, char* argv[]) -> int
{
    std::thread t1(func1);
    std::thread t2(func2);
    t1.join();
    t2.join();

    return 0;
}