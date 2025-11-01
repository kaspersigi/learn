#pragma once

#include <string>

enum class Status {
    OK = true,
    Error = false,
};

class MyWorker {
public:
    MyWorker();
    ~MyWorker();

    static Status callback(int value);
    void execute(int value, const std::string& str) const;

protected:
    MyWorker(const MyWorker&) = delete;
    MyWorker(MyWorker&&) = delete;
    MyWorker& operator=(const MyWorker&) = delete;
    MyWorker& operator=(MyWorker&&) = delete;

private:
    int main_worker() const;
    int child_worker(int value, const std::string& str) const;
    typedef Status (*_callback)(size_t);
    _callback _cb = nullptr;
};