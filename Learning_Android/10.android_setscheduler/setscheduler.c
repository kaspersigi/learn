#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE
#include "ftrace.h"
#include "unistd.h"
#include <android/log.h>
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
    ftrace_duration_begin("ChildThread");
    pid_t tid = gettid();
    int old_sched = sched_getscheduler(tid);
    if (-1 == old_sched) {
        LOGE("sched_getscheduler -- lzz");
        return (void*)-1;
    } else {
        LOGI("old_sched = %d -- lzz", old_sched);
    }
    sleep(1);

    int new_policy = SCHED_RR;
    struct sched_param new_param;
    new_param.sched_priority = sched_get_priority_min(new_policy);
    if (-1 == sched_setscheduler(tid, new_policy, &new_param)) {
        LOGE("sched_setscheduler -- lzz");
        return (void*)-1;
    }
    sleep(1);

    int new_sched = sched_getscheduler(tid);
    if (-1 == new_sched) {
        LOGE("sched_getscheduler -- lzz");
        return (void*)-1;
    } else {
        LOGI("new_sched = %d -- lzz", new_sched);
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