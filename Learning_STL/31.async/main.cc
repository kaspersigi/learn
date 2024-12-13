#include <chrono>
#include <future>
#include <iostream>
#include <thread>

int func()
{
    std::cout << "child thread start sleeping." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::cout << "child thread end sleeping." << std::endl;
    std::cout << "this is a child thread." << std::endl;
    return 5;
}

auto main(int argc, char* argv[]) -> int
{
    // std::future<int> result { std::async(std::launch::async, func) };
    // std::future<int> result { std::async(std::launch::deferred, func) };
    std::future<int> result { std::async(func) }; // 默认策略，还是倾向异步
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    std::cout << "main thread start sleeping." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(8));
    std::cout << "main thread end sleeping." << std::endl;
    std::cout << result.get() << std::endl;
    std::cout << "this is a main thread." << std::endl;
    return 0;
}