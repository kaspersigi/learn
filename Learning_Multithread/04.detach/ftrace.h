#pragma once

#include <mutex>

class Ftrace {
public:
    static int trace_dur_begin(const char* message);
    static int trace_dur_end();

private:
    static bool trace_enable();
    static std::mutex _mutex;
    static int _fd;
};