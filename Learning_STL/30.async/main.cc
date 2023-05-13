#include <chrono>
#include <future>
#include <iostream>
#include <thread>

int func()
{
    std::cout << "this is a child thread." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::cout << "child thread dead." << std::endl;
    return 5;
}

auto main(int argc, char* argv[]) -> int
{
    std::future<int> result { std::async(std::launch::async, func) };
    std::cout << "sleeping 8s." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(8));
    std::cout << result.get() << std::endl;
    std::cout << "this is a main thread." << std::endl;
    return 0;
}