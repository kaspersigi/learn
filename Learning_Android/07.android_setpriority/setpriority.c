#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE
#include "ftrace.h"
#include "unistd.h"
#include <android/log.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/resource.h>

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "LZZ_CTEST"

#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

void* func(void* arg)
{
    ftrace_duration_begin("ChildThread");
    pid_t tid = gettid();
    int current_nice, new_nice;
    current_nice = getpriority(PRIO_PROCESS, tid);
    if (-1 == current_nice && 0 != errno) {
        LOGE("getpriority failed -- lzz");
    } else {
        LOGI("tid = %d, current_nice = %d -- lzz", tid, current_nice);
    }
    sleep(1);

    new_nice = -10;
    int ret = setpriority(PRIO_PROCESS, tid, new_nice);
    if (ret < 0) {
        LOGE("setpriority failed -- lzz");
    } else {
        LOGI("tid = %d, new_nice = %d -- lzz", tid, new_nice);
    }
    sleep(1);

    current_nice = getpriority(PRIO_PROCESS, tid);
    if (-1 == current_nice && 0 != errno) {
        LOGE("getpriority failed -- lzz");
    } else {
        LOGI("tid = %d, current_nice = %d -- lzz", tid, current_nice);
    }
    sleep(1);
    ftrace_duration_end();

    return (void*)0;
}

int main(int argc, char* argv[])
{
    if (!ftrace_init())
        return -1;
    ftrace_duration_begin("MainThread");

    pthread_t tid;
    int ret = pthread_create(&tid, NULL, func, NULL);
    if (0 != ret) {
        LOGE("create new thread failed! -- lzz");
        return -1;
    }

    pthread_join(tid, NULL);
    ftrace_duration_end();
    ftrace_close();

    return 0;
}