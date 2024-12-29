#include <android/trace.h>
#include <iostream>
#include <thread>

auto main(int argc, char* argv[]) -> int
{
    if (ATrace_isEnabled())
        std::cout << "ATrace is enable!" << std::endl;
    else
        std::cout << "ATrace is disable!" << std::endl;

    ATrace_beginSection("MyATrace");
    for (size_t i = 0; i < 500; ++i) {
        std::cout << "Hello World!" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    ATrace_endSection();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    return 0;
}