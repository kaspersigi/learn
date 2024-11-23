#include "MyWorker.h"
#include <iostream>

int MyWorker::main_worker(Callback cb)
{
    for (size_t i = 0; i < 60; ++i) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << __func__ << ": " << i << std::endl;
    }
    cb();
    return 0;
}

void MyWorker::callback()
{
    std::cout << __func__ << ": " << "Hello world!" << std::endl;
}