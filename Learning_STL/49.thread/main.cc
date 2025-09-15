#include <chrono>
#include <iostream>
#include <thread>

void func()
{
    const auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < 1000; ++i)
        std::cout << 'a' << std::flush;
    std::cout << std::endl;
    const auto end = std::chrono::high_resolution_clock::now();
    const std::chrono::duration<double, std::milli> elapsed = end - start;

    std::cout << "cost time " << elapsed << "." << std::endl;
}

auto main(int argc, char* argv[]) -> int
{
    std::thread t(func);
    t.join();

    return 0;
}