#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE
#include "ftrace.h"
#include <android/log.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "LZZ_CTEST"

#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

void* func(void* arg)
{
    trace_dur_begin("ChildThread");
    LOGI("child thread nice = %d -- lzz", nice(0));
    sleep(1);

    int new_nice = nice(-10);
    if (-1 == new_nice && 0 != errno) {
        LOGE("child thread nice() failed -- lzz");
    } else {
        LOGI("child thread new_nice = %d -- lzz", new_nice);
    }
    sleep(1);

    LOGI("child thread nice = %d -- lzz", nice(0));
    sleep(1);
    trace_dur_end();

    return (void*)0;
}

int main(int argc, char* argv[])
{
    if (!trace_open()) {
        LOGE("trace_open filed! -- lzz");
        return -1;
    }
    int ret = trace_dur_begin("MainThread");
    if (ret <= 0) {
        LOGE("trace_dur_begin filed!");
        return -1;
    }

    LOGI("main thread nice = %d -- lzz", nice(0));
    pthread_t tid;
    ret = pthread_create(&tid, NULL, func, NULL);
    if (0 != ret) {
        LOGE("create new thread failed! -- lzz");
        return -1;
    }

    pthread_join(tid, NULL);
    LOGI("main thread nice = %d -- lzz", nice(0));
    ret = trace_dur_end();
    if (ret <= 0) {
        LOGE("trace_dur_end filed! -- lzz");
        return -1;
    }
    trace_close();

    return 0;
}