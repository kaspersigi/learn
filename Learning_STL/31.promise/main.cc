#include <chrono>
#include <future>
#include <iostream>
#include <thread>

void func(std::promise<int>& p)
{
    std::cout << "child thread start sleeping." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::cout << "child thread end sleeping." << std::endl;
    int answer = 5;
    p.set_value(answer);
    std::cout << "this is a child thread." << std::endl;
}

auto main(int argc, char* argv[]) -> int
{
    std::promise<int> p;
    std::thread t { func, std::ref(p) };
    t.detach();
    std::future<int> f { p.get_future() };
    std::cout << f.get() << std::endl;
    std::cout << "Hello World!" << std::endl;
    return 0;
}