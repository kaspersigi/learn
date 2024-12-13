#include "MyWorker.h"
#include <memory>

auto main(int argc, char* argv[]) -> int
{
    pthread_t tid = pthread_self();
    std::string s;
    s = std::string(__PRETTY_FUNCTION__) + ": tid = " + std::to_string(tid);
    std::cout << s << std::endl;
    auto mw = std::make_shared<MyWorker>();
    auto mw_t = std::thread(&MyWorker::execute, mw, 9, std::string("Hello world!"));
    std::this_thread::sleep_for(std::chrono::seconds(10));
    mw_t.join();
    std::this_thread::sleep_for(std::chrono::seconds(30));
    std::cout << __PRETTY_FUNCTION__ << " dead!" << std::endl;
    // 说明子线程创建的子线程分离后，并不会因为子线程被销毁而销毁，只会因为主线程销毁而销毁
    return 0;
}