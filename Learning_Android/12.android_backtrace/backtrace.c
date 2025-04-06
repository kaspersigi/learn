#define _POSIX_C_SOURCE 200809L

#include <android/log.h>
#include <dlfcn.h>
#include <signal.h>
#include <stdbool.h>
#include <sys/types.h>
#include <unistd.h>
#include <unwind.h>

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "LZZ_CTEST"

#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

// http://dogee.tech/2021-08-16_unwind%E4%BD%BF%E7%94%A8%E6%8C%87%E5%8C%97.html

struct backtrace_stack {
    void** current;
    void** end;
};

static _Unwind_Reason_Code _unwind_callback(struct _Unwind_Context* context, void* data)
{
    struct backtrace_stack* state = (struct backtrace_stack*)(data);
    uintptr_t pc = _Unwind_GetIP(context);
    if (pc) {
        if (state->current == state->end) {
            return _URC_END_OF_STACK;
        } else {
            *state->current++ = (void*)(pc);
        }
    }
    return _URC_NO_REASON;
}

static size_t _fill_backtraces_buffer(void** buffer, size_t max)
{
    struct backtrace_stack stack = { buffer, buffer + max };
    _Unwind_Backtrace(_unwind_callback, &stack);
    return stack.current - buffer;
}

#if 0
typedef struct {
    const char* dli_fname;
    void* dli_fbase;
    const char* dli_sname;
    void* dli_saddr;
} Dl_info;
#endif

void backtrace()
{
    void* buffer[30];
    void* addr;
    int count = _fill_backtraces_buffer(buffer, 30);
    for (int index = 2; index < count; ++index) {
        addr = buffer[index];
        Dl_info info;
        if (dladdr(addr, &info)) {
            LOGE("# %d: pc:%p offset:[0x%-8lx] %s(%s) -- lzz",
                index - 2,
                addr,
                addr - info.dli_fbase,
                info.dli_fname,
                info.dli_sname);
        }
    }
}

void func(int signum)
{
    LOGI("backtrace receive signal %d -- lzz", signum);
    LOGI("backtrace E -- lzz");
    backtrace();
    LOGI("backtrace X -- lzz");
    return;
}

int main(int argc, char* argv[])
{
    LOGI("backtrace start -- lzz");
    LOGI("backtrace pid = %d -- lzz", getpid());
    while (true) {
        signal(SIGUSR1, func);
        pause();
    }
    LOGI("backtrace end -- lzz");

    return 0;
}