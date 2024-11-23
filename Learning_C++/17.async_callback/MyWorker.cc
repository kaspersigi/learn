#include "MyWorker.h"
#include <iostream>

MyWorker::MyWorker()
    : _cb(_callback)
{
}
int MyWorker::main_worker()
{
    for (size_t i = 0; i < 60; ++i) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << __func__ << ": " << i << std::endl;
        if (10 == i) {
            auto t = _create_thread(9, std::string("hello world!"), _callback);
            t.detach();
        }
    }
    return 0;
}

void MyWorker::child_worker_c(int value, const std::string& str, callback cb)
{
    for (size_t i = 0; i < 30; ++i) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << __func__ << ": " << i << ", value = " << value << ", " << str << std::endl;
    }
}

std::thread MyWorker::_create_thread(int value, const std::string& str, callback cb)
{
    return std::thread(&MyWorker::child_worker_c, this, value, std::ref(str), cb);
}

void MyWorker::_callback()
{
}