#include "ftrace.h"
#include <fcntl.h>
#include <format>
#include <print>
#include <unistd.h>

int Ftrace::_fd = -1;
std::mutex Ftrace::_mutex;

// Helper: Thread-safe write to ftrace
int Ftrace::_write_to_ftrace(const std::string& str)
{
    if (_fd < 0 && !ftrace_enable())
        return -1;
    std::lock_guard<std::mutex> lock(_mutex);
    int ret = write(_fd, str.c_str(), str.size());
    // std::println("{}: wrote {} bytes: {}", __PRETTY_FUNCTION__, ret, str);
    return ret;
}

//----- Duration Events (B/E/X) -----
int Ftrace::ftrace_duration_begin(const std::string& message)
{
    return _write_to_ftrace(std::format("B|{}|{}", getpid(), message));
}

int Ftrace::ftrace_duration_end()
{
    return _write_to_ftrace(std::format("E|{}", getpid()));
}

int Ftrace::ftrace_duration_complete(const std::string& message, uint64_t duration_ns)
{
    return _write_to_ftrace(std::format("X|{}|{}|{}", getpid(), message, duration_ns));
}

//----- Instant Events (i/I) -----
int Ftrace::ftrace_instant(const std::string& message)
{
    return _write_to_ftrace(std::format("I|{}|{}", getpid(), message));
}

//----- Counter Events (C) -----
int Ftrace::ftrace_counter_set(const std::string& message, size_t count)
{
    return _write_to_ftrace(std::format("C|{}|{}|{}", getpid(), message, count));
}

int Ftrace::ftrace_counter_zero(const std::string& message)
{
    return ftrace_counter_set(message, 0);
}

//----- Async Events (b/n/e) -----
int Ftrace::ftrace_async_begin(const std::string& id, const std::string& message)
{
    return _write_to_ftrace(std::format("b|{}|{}|{}", getpid(), id, message));
}

int Ftrace::ftrace_async_instant(const std::string& id, const std::string& message)
{
    return _write_to_ftrace(std::format("n|{}|{}|{}", getpid(), id, message));
}

int Ftrace::ftrace_async_end(const std::string& id)
{
    return _write_to_ftrace(std::format("e|{}|{}", getpid(), id));
}

//----- Flow Events (s/t/f) -----
int Ftrace::ftrace_flow_start(const std::string& flow_id, const std::string& message)
{
    return _write_to_ftrace(std::format("s|{}|{}|{}", getpid(), flow_id, message));
}

int Ftrace::ftrace_flow_step(const std::string& flow_id, const std::string& message)
{
    return _write_to_ftrace(std::format("t|{}|{}|{}", getpid(), flow_id, message));
}

int Ftrace::ftrace_flow_end(const std::string& flow_id)
{
    return _write_to_ftrace(std::format("f|{}|{}", getpid(), flow_id));
}

//----- Object Events (N/O/D) -----
int Ftrace::ftrace_obj_create(const std::string& obj, const std::string& message)
{
    return _write_to_ftrace(std::format("N|{}|{}|{}", getpid(), obj, message));
}

int Ftrace::ftrace_obj_snapshot(const std::string& obj, const std::string& message)
{
    return _write_to_ftrace(std::format("O|{}|{}|{}", getpid(), obj, message));
}

int Ftrace::ftrace_obj_destroy(const std::string& obj)
{
    return _write_to_ftrace(std::format("D|{}|{}", getpid(), obj));
}

//----- Metadata (M) and Memory Dump (V/v) -----
int Ftrace::ftrace_metadata(const std::string& key, const std::string& value)
{
    return _write_to_ftrace(std::format("M|{}|{}", key, value));
}

int Ftrace::ftrace_memory_dump(bool is_global, const std::string& data)
{
    char phase = is_global ? 'V' : 'v';
    return _write_to_ftrace(std::format("{}|{}|{}", phase, getpid(), data));
}

//----- System Control -----
bool Ftrace::ftrace_enable()
{
    if (_fd >= 0)
        return true;
    _fd = open("/sys/kernel/tracing/trace_marker", O_CLOEXEC | O_WRONLY);
    if (_fd < 0) {
        std::println("Failed to open trace_marker!");
        return false;
    }
    return true;
}

void Ftrace::ftrace_disable()
{
    if (_fd >= 0) {
        close(_fd);
        _fd = -1;
    }
}