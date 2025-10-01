#include "MyWorker.h"
#include <future>
#include <iostream>
#include <thread>

int ChildWorker::child_worker(int value, const std::string& str, std::promise<int>& p)
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
    std::promise<int> p;
    std::future<int> f { p.get_future() };
    std::thread t { &ChildWorker::child_worker, _cw, value, std::ref(str), std::ref(p) };
    t.detach();
    [[maybe_unused]] int ret1 = main_worker();
    [[maybe_unused]] int ret2 = f.get();
}