#include "MyWorker.h"
#include <iostream>
#include <thread>

void MyWorker::execute(int value, const std::string& str) const
{
    auto t = std::thread(&MyWorker::child_worker, this, value, std::ref(str));
    main_worker();
    t.join();
}

int MyWorker::main_worker() const
{
    for (size_t i = 0; i < 60; ++i) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << __PRETTY_FUNCTION__ << ": " << i << std::endl;
    }
    return 0;
}

int MyWorker::child_worker(int value, const std::string& str) const
{
    for (size_t i = 0; i < 30; ++i) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << __PRETTY_FUNCTION__ << ": " << i << ", value = " << value << ", " << str << std::endl;
    }
    return 0;
}