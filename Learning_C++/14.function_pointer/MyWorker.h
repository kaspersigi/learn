#pragma once

#include <string>
#include <thread>

class MyWorker {
public:
    MyWorker() = default;
    ~MyWorker() = default;
    typedef void (*Callback)();
    int main_worker(Callback cb);
    void callback();

protected:
    MyWorker(const MyWorker&) = delete;
    MyWorker(MyWorker&&) = delete;
    MyWorker& operator=(const MyWorker&) = delete;
    MyWorker& operator=(MyWorker&&) = delete;
};