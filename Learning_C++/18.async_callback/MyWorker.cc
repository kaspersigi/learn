#include "MyWorker.h"
#include <functional>
#include <future>
#include <iostream>
#include <thread>

MyWorker::MyWorker()
{
}

MyWorker::~MyWorker()
{
    _cb = nullptr;
}

Status MyWorker::callback(int value)
{
    if (0 == value % 20) {
        std::cout << __PRETTY_FUNCTION__ << ": value = " << value << std::endl;
    } else {
        std::cout << __PRETTY_FUNCTION__ << " Nothing to do" << std::endl;
    }
    return Status::OK;
}

void MyWorker::execute(int value, const std::string& str) const
{
    std::future<int> ret1(std::async(&MyWorker::main_worker, this));
    std::future<int> ret2(std::async(&MyWorker::child_worker, this, value, std::ref(str)));
    ret1.get();
    ret2.get();
}

int MyWorker::main_worker() const
{
    for (size_t i = 0; i < 60; ++i) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << __PRETTY_FUNCTION__ << ": " << i << std::endl;
        if (0 == i % 10) {
            _cb(i);
        }
    }
    return 0;
}

int MyWorker::child_worker(int value, const std::string& str) const
{
    for (size_t i = 0; i < 30; ++i) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << __PRETTY_FUNCTION__ << ": " << i << ", value = " << value << ", " << str << std::endl;
        if (0 == i % 10) {
            _cb(i);
        }
    }
    return 0;
}