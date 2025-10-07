#include "MyWorker.h"
#include <future>
#include <iostream>
#include <thread>

int ChildWorker::child_worker(int value, const std::string& str)
{
    for (size_t i = 0; i < 30; ++i) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << __PRETTY_FUNCTION__ << ": " << i << ", value = " << value << ", " << str << std::endl;
    }
    return 0;
}

int MainWorker::main_worker()
{
    for (size_t i = 0; i < 60; ++i) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << __PRETTY_FUNCTION__ << ": " << i << std::endl;
    }
    return 0;
}

void MainWorker::execute(int value, const std::string& str)
{
#if 0
    std::future<int> ret1(std::async(&MainWorker::main_worker, this));
    int ret2 = _cw->child_worker(value, str);
    ret1.get();
#else
    std::future<int> ret1(std::async(&ChildWorker::child_worker, _cw, value, std::ref(str)));
    [[maybe_unused]] int ret2 = main_worker();
    ret1.get();
#endif
}