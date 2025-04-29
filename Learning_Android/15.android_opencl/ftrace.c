#include "ftrace.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static int g_ftrace_fd = -1;
static pthread_mutex_t g_ftrace_mutex = PTHREAD_MUTEX_INITIALIZER;

// 内部函数：线程安全写入
static int _ftrace_write(const char* str)
{
    if (g_ftrace_fd < 0)
        return -1;

    pthread_mutex_lock(&g_ftrace_mutex);
    int ret = write(g_ftrace_fd, str, strlen(str));
    pthread_mutex_unlock(&g_ftrace_mutex);

    return ret;
}

// 初始化 ftrace
bool ftrace_init(void)
{
    if (g_ftrace_fd >= 0)
        return true;

    g_ftrace_fd = open("/sys/kernel/tracing/trace_marker", O_WRONLY);
    if (g_ftrace_fd < 0) {
        perror("Failed to open trace_marker");
        return false;
    }
    return true;
}

// 关闭 ftrace
void ftrace_close(void)
{
    if (g_ftrace_fd >= 0) {
        close(g_ftrace_fd);
        g_ftrace_fd = -1;
    }
}

//----- Duration Events (B/E/X) -----
int ftrace_duration_begin(const char* message)
{
    char buf[256];
    snprintf(buf, sizeof(buf), "B|%d|%s", getpid(), message);
    return _ftrace_write(buf);
}

int ftrace_duration_end(void)
{
    char buf[64];
    snprintf(buf, sizeof(buf), "E|%d", getpid());
    return _ftrace_write(buf);
}

int ftrace_duration_complete(const char* message, uint64_t duration_us)
{
    char buf[256];
    snprintf(buf, sizeof(buf), "X|%d|%s|%lu", getpid(), message, duration_us);
    return _ftrace_write(buf);
}

//----- Instant Events (I) -----
int ftrace_instant(const char* message)
{
    char buf[256];
    snprintf(buf, sizeof(buf), "I|%d|%s", getpid(), message);
    return _ftrace_write(buf);
}

//----- Counter Events (C) -----
int ftrace_counter_set(const char* message, size_t count)
{
    char buf[256];
    snprintf(buf, sizeof(buf), "C|%d|%s|%zu", getpid(), message, count);
    return _ftrace_write(buf);
}

int ftrace_counter_zero(const char* message)
{
    return ftrace_counter_set(message, 0);
}

//----- Async Events (b/n/e or S/T/F) -----
int ftrace_async_start(const char* message, const char* id)
{
    char buf[256];
    snprintf(buf, sizeof(buf), "S|%d|%s|%s", getpid(), message, id);
    return _ftrace_write(buf);
}

int ftrace_async_step(const char* message, const char* id)
{
    char buf[256];
    snprintf(buf, sizeof(buf), "T|%d|%s|%s", getpid(), message, id);
    return _ftrace_write(buf);
}

int ftrace_async_end(const char* message, const char* id)
{
    char buf[256];
    snprintf(buf, sizeof(buf), "F|%d|%s|%s", getpid(), message, id);
    return _ftrace_write(buf);
}

//----- Flow Events (s/t/f) -----
int ftrace_flow_start(const char* message, const char* id)
{
    char buf[256];
    snprintf(buf, sizeof(buf), "s|%d|%s|%s", getpid(), message, id);
    return _ftrace_write(buf);
}

int ftrace_flow_step(const char* message, const char* id)
{
    char buf[256];
    snprintf(buf, sizeof(buf), "t|%d|%s|%s", getpid(), message, id);
    return _ftrace_write(buf);
}

int ftrace_flow_end(const char* message, const char* id)
{
    char buf[256];
    snprintf(buf, sizeof(buf), "f|%d|%s|%s", getpid(), message, id);
    return _ftrace_write(buf);
}

//----- Object Events (N/O/D) -----
int ftrace_obj_create(const char* obj, const char* message)
{
    char buf[256];
    snprintf(buf, sizeof(buf), "N|%d|%s|%s", getpid(), obj, message);
    return _ftrace_write(buf);
}

int ftrace_obj_snapshot(const char* obj, const char* message)
{
    char buf[256];
    snprintf(buf, sizeof(buf), "O|%d|%s|%s", getpid(), obj, message);
    return _ftrace_write(buf);
}

int ftrace_obj_destroy(const char* obj)
{
    char buf[256];
    snprintf(buf, sizeof(buf), "D|%d|%s", getpid(), obj);
    return _ftrace_write(buf);
}

//----- Metadata (M) and Memory Dump (V/v) -----
int ftrace_metadata(const char* key, const char* value)
{
    char buf[256];
    snprintf(buf, sizeof(buf), "M|%s|%s", key, value);
    return _ftrace_write(buf);
}

int ftrace_memory_dump(bool is_global, const char* data)
{
    char buf[256];
    snprintf(buf, sizeof(buf), "%c|%d|%s", is_global ? 'V' : 'v', getpid(), data);
    return _ftrace_write(buf);
}