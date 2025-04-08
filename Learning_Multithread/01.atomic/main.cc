#include <atomic>
#include <print>
#include <thread>

std::atomic<int> i(0);

void func1()
{
    while (i < 100) {
        if (0 == i % 2) {
            std::print("a");
            i++;
        }
    }
}

void func2()
{
    while (i < 100) {
        if (1 == i % 2) {
            std::print("b");
            i++;
        }
    }
}

auto main(int argc, char* argv[]) -> int
{
    std::thread t1(func1);
    std::thread t2(func2);
    t1.join();
    t2.join();

    return 0;
}