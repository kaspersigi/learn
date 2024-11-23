#pragma once

#include <string>
#include <thread>

class MyWorker {
public:
    // MyWorker() = default;
    ~MyWorker() = default;
    typedef void (*callback)();
    int main_worker();
    void child_worker_c(int value, const std::string& str, callback cb);

protected:
    MyWorker(const MyWorker&) = delete;
    MyWorker(MyWorker&&) = delete;
    MyWorker& operator=(const MyWorker&) = delete;
    MyWorker& operator=(MyWorker&&) = delete;

private:
    std::thread _create_thread(int value, const std::string& str, callback c);
    void _callback();
    callback _cb = nullptr;
};