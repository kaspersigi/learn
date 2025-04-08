#include <atomic>
#include <print>
#include <thread>

static std::atomic<int> i(0);

void func1()
{
    while (i < 100) {
        int current = i.load();
        if (current < 100 && 0 == current % 2) {
            std::print("a");
            i.fetch_add(1);
        } else {
            std::this_thread::yield();
        }
    }
}

void func2()
{
    while (i < 100) {
        int current = i.load();
        if (current < 100 && 1 == current % 2) {
            std::print("b");
            i.fetch_add(1);
        } else {
            std::this_thread::yield();
        }
    }
}

int main(int argc, char* argv[])
{
    std::thread t1(func1);
    std::thread t2(func2);
    t1.join();
    t2.join();

    return 0;
}