#pragma once

#include <android/log.h>
#include <sys/types.h>
#include <unwind.h>

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "Backtrace"

#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

// http://dogee.tech/2021-08-16_unwind%E4%BD%BF%E7%94%A8%E6%8C%87%E5%8C%97.html

#if 0
typedef struct {
    const char* dli_fname;
    void* dli_fbase;
    const char* dli_sname;
    void* dli_saddr;
} Dl_info;
#endif

typedef struct backtrace_stack {
    void** current;
    void** end;
} backtrace_stack;

static _Unwind_Reason_Code _unwind_callback(struct _Unwind_Context* context, void* data);

static size_t _fill_backtraces_buffer(void** buffer, size_t max);

void backtrace();