#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE
#include <android/log.h>
#include <errno.h>
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