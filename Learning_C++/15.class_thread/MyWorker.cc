#include "MyWorker.h"
#include <string>

void MyWorker::execute(int value, const std::string& str) const
{
#if 1
    // auto tid = std::this_thread::get_id();
    pthread_t tid = pthread_self();
    std::string s;
    s = std::string(__PRETTY_FUNCTION__) + ": tid = " + std::to_string(tid);
    std::cout << s << std::endl;
    auto cw = std::thread(&MyWorker::child_worker, this, value, std::ref(str));
    cw.detach();
    auto mw = std::thread(&MyWorker::main_worker, this);
    mw.detach();
    std::this_thread::sleep_for(std::chrono::seconds(10));
#else
    auto cw = std::thread(&MyWorker::child_worker, this, value, std::ref(str));
    auto mw = std::thread(&MyWorker::main_worker, this);
    cw.join();
#endif
    std::cout << __PRETTY_FUNCTION__ << " dead!" << std::endl;
}

int MyWorker::main_worker() const
{
    // auto tid = std::this_thread::get_id();
    pthread_t tid = pthread_self();
    std::string s;
    for (size_t i = 0; i < 60; ++i) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        s = std::string(__PRETTY_FUNCTION__) + ": " + std::to_string(i) + ", tid = " + std::to_string(tid);
        std::cout << std::endl;
        std::cout << s << std::endl;
    }
    std::cout << __PRETTY_FUNCTION__ << " dead!" << std::endl;
    return 0;
}

int MyWorker::child_worker(int value, const std::string& str) const
{
    // auto tid = std::this_thread::get_id();
    pthread_t tid = pthread_self();
    std::string s;
    for (size_t i = 0; i < 30; ++i) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        s = std::string(__PRETTY_FUNCTION__) + ": " + std::to_string(i) + ", value = " + std::to_string(value) + ", " + str + ", tid = " + std::to_string(tid);
        std::cout << std::endl;
        std::cout << s << std::endl;
    }
    std::cout << __PRETTY_FUNCTION__ << " dead!" << std::endl;
    return 0;
}