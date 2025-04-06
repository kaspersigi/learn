#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE
#include <android/log.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "LZZ_CTEST"

#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

static const int WRITE_OFFSET = 32;
static int g_trace_marker_fd = -1;
static pthread_mutex_t mutex;

void trace_begin(char* message)
{
    int length = strlen(message);
    char buf[length + WRITE_OFFSET];
    size_t len = sprintf(buf, "B|%d|%s", getpid(), message);
    pthread_mutex_trylock(&mutex);
    write(g_trace_marker_fd, buf, len);
    pthread_mutex_unlock(&mutex);
}

void trace_end()
{
    const char buf[2] = { 'E', '|' };
    pthread_mutex_trylock(&mutex);
    write(g_trace_marker_fd, buf, sizeof(buf));
    pthread_mutex_unlock(&mutex);
}

void* func(void* arg)
{
    trace_begin("CHildThread");
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
    trace_end();

    return (void*)0;
}

int main(int argc, char* argv[])
{
    if (g_trace_marker_fd == -1) {
        g_trace_marker_fd = open("/sys/kernel/tracing/trace_marker", O_WRONLY);
        if (g_trace_marker_fd == -1) {
            g_trace_marker_fd = open("/sys/kernel/debug/tracing/trace_marker", O_WRONLY);
        }
    }
    if (g_trace_marker_fd) {
        LOGI("open trace_market success! -- lzz");
    } else {
        LOGE("open trace_market failed! -- lzz");
        exit(-1);
    }

    trace_begin("MainThread");
    LOGI("main thread nice = %d -- lzz", nice(0));
    pthread_t tid;
    int ret = pthread_create(&tid, NULL, func, NULL);
    if (0 != ret) {
        LOGE("create new thread failed! -- lzz");
        return -1;
    }

    pthread_join(tid, NULL);
    close(g_trace_marker_fd);
    LOGI("main thread nice = %d -- lzz", nice(0));
    trace_end();

    return 0;
}