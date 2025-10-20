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
    LOGI("child thread nice = %d -- lzz", nice(0));

    pthread_t tid = pthread_self();
    int old_prio, new_prio, current_prio;
    int old_policy, new_policy, current_policy;
    struct sched_param old_param, new_param, current_param;

    if (pthread_getschedparam(tid, &old_policy, &old_param) != 0) {
        LOGE("pthread_getschedparam -- lzz");
        return (void*)-1;
    } else {
        LOGI("old_policy = %d, old_prio = %d -- lzz", old_policy, old_param.sched_priority);
    }
    sleep(1);

    new_policy = SCHED_RR;
    new_param.sched_priority = sched_get_priority_min(new_policy);
    if (pthread_setschedparam(tid, new_policy, &new_param) != 0) {
        LOGE("pthread_setschedparam -- lzz");
        return (void*)-1;
    }
    sleep(1);

    if (pthread_getschedparam(tid, &current_policy, &current_param) != 0) {
        LOGE("pthread_getschedparam -- lzz");
        return (void*)-1;
    } else {
        LOGI("current_policy = %d, current_prio = %d -- lzz", current_policy, current_param.sched_priority);
    }
    sleep(1);
    ftrace_close();

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