#include "ftrace.h"

#include <format>
#include <print>

extern "C" {
#include <fcntl.h>
#include <unistd.h>
}

int Ftrace::_fd = -1;
std::mutex Ftrace::_mutex;

int Ftrace::trace_dur_begin(const std::string& message)
{
    if (trace_enable()) {
        const std::string str = std::format("{}|{}|{}", 'B', getpid(), message);
        _mutex.lock();
        int ret = write(_fd, str.c_str(), str.size());
        _mutex.unlock();
        std::println("{}: write {} bytes!", __PRETTY_FUNCTION__, ret);
        return ret;
    } else {
        return 0;
    }
}

int Ftrace::trace_dur_end()
{
    if (trace_enable()) {
        const std::string str = std::format("{}|{}", 'E', getpid());
        _mutex.lock();
        int ret = write(_fd, str.c_str(), str.size());
        _mutex.unlock();
        std::println("{}: write {} bytes!", __PRETTY_FUNCTION__, ret);
        return ret;
    } else {
        return 0;
    }
}

bool Ftrace::trace_enable()
{
    bool enable = false;
    if (_fd < 0) {
        _fd = open("/sys/kernel/tracing/trace_marker", O_WRONLY);
        if (_fd > 0) {
            enable = true;
            std::println("{}: open trace_marker success!\n", __PRETTY_FUNCTION__);
        } else {
            std::println("{}: open trace_marker failed!\n", __PRETTY_FUNCTION__);
        }
    } else {
        enable = true;
        std::println("{}: open trace_marker already!\n", __PRETTY_FUNCTION__);
    }
    return enable;
}