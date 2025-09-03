#pragma once

#include <iostream>
#include <string>
#include <thread>

extern "C" {
#include <pthread.h>
}

class MyWorker
{
public:
    MyWorker() = default;
    ~MyWorker() = default;

    void execute(int value, const std::string& str) const;

protected:
    MyWorker(const MyWorker&) = delete;
    MyWorker(MyWorker&&) = delete;
    MyWorker& operator = (const MyWorker&) = delete;
    MyWorker& operator = (MyWorker&&) = delete;

private:
    int main_worker() const;
    int child_worker(int value, const std::string& str) const;
};