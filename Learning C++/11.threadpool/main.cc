#include "threadpool.h"
#include <iostream>

void* function(void* arg)
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Hello World!" << std::endl;
    return nullptr;
}

auto main(int argc, char* argv[]) -> int
{
    ThreadPool threadpool;
    for (int i = 0; i < 10; ++i) {
        std::cout << "prepare adding task..." << std::endl;
        threadpool.add_task(function, nullptr);
    }

    return 0;
}