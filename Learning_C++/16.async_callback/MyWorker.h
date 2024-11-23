#pragma once

#include <string>
#include <thread>

class MyWorker {
public:
    MyWorker() = default;
    ~MyWorker() = default;

    int main_worker();
    void child_worker(int value, const std::string& str);

protected:
    MyWorker(const MyWorker&) = delete;
    MyWorker(MyWorker&&) = delete;
    MyWorker& operator=(const MyWorker&) = delete;
    MyWorker& operator=(MyWorker&&) = delete;

private:
    std::thread create_thread(int value, const std::string& str);
};