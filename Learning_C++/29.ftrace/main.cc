#include "ftrace.h"
#include <chrono>
#include <thread>

auto main(int argc, char* argv[]) -> int
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    Ftrace::trace_dur_begin("MyFtrace");
    std::this_thread::sleep_for(std::chrono::seconds(3));
    Ftrace::trace_dur_end();

    return 0;
}