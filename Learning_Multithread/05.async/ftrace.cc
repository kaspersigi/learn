#include "ftrace.h"
#include <fcntl.h>
#include <print>
#include <string.h>
#include <unistd.h>

static const int WRITE_OFFSET = 32;

int Ftrace::_fd = -1;
std::mutex Ftrace::_mutex;

int Ftrace::trace_dur_begin(const char* message)
{
    if (trace_enable()) {
        int length = strlen(message);
        char buf[length + WRITE_OFFSET];
        size_t len = sprintf(buf, "B|%d|%s", getpid(), message);
        _mutex.lock();
        int ret = write(_fd, buf, len);
        std::println("{}: write {} bytes!", __PRETTY_FUNCTION__, ret);
        _mutex.unlock();
        return ret;
    } else {
        return 0;
    }
}

int Ftrace::trace_dur_end()
{
    if (trace_enable()) {
        char buf[WRITE_OFFSET];
        size_t len = sprintf(buf, "E|%d", getpid());
        _mutex.lock();
        int ret = write(_fd, buf, len);
        std::println("{}: write {} bytes!", __PRETTY_FUNCTION__, ret);
        _mutex.unlock();
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
    }
    return enable;
}