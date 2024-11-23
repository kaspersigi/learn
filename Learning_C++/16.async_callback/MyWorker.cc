#include "MyWorker.h"
#include <iostream>

int MyWorker::main_worker()
{
    for (size_t i = 0; i < 60; ++i) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << __func__ << ": " << i << std::endl;
        if (10 == i) {
            auto t = create_thread(9, std::string("hello world!"));
            t.detach();
        }
    }
    return 0;
}

void MyWorker::child_worker(int value, const std::string& str)
{
    for (size_t i = 0; i < 30; ++i) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << __func__ << ": " << i << ", value = " << value << ", " << str << std::endl;
    }
}

std::thread MyWorker::create_thread(int value, const std::string& str)
{
    return std::thread(&MyWorker::child_worker, this, value, std::ref(str));
}