#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE
#include "ftrace.h"
#include <errno.h>
#include <sys/resource.h>

void* func(void* arg)
{
    trace_dur_begin("ChildThread");
    pid_t tid = gettid();
    int current_nice, new_nice;
    current_nice = getpriority(PRIO_PROCESS, tid);
    if (-1 == current_nice && 0 != errno) {
        perror("getpriority failed");
    } else {
        printf("tid = %d, current_nice = %d\n", tid, current_nice);
    }

    new_nice = -10;
    int ret = setpriority(PRIO_PROCESS, tid, new_nice);
    if (ret < 0) {
        perror("setpriority failed");
    } else {
        printf("tid = %d, new_nice = %d\n", tid, new_nice);
    }

    current_nice = getpriority(PRIO_PROCESS, tid);
    if (-1 == current_nice && 0 != errno) {
        perror("getpriority failed");
    } else {
        printf("tid = %d, current_nice = %d\n", tid, current_nice);
    }
    trace_dur_end();

    return (void*)0;
}

int main(int argc, char* argv[])
{
    if (!trace_open()) {
        printf("%s: trace_open filed!\n", __PRETTY_FUNCTION__);
        return -1;
    }
    int ret = trace_dur_begin("MyFtrace");
    if (ret <= 0) {
        printf("%s: trace_dur_begin filed!\n", __PRETTY_FUNCTION__);
        return -1;
    }

    pthread_t tid;
    ret = pthread_create(&tid, NULL, func, NULL);
    if (0 != ret) {
        printf("create new thread failed!\n");
        return -1;
    }
    pthread_join(tid, NULL);

    ret = trace_dur_end();
    if (ret <= 0) {
        printf("%s: trace_dur_end filed!\n", __PRETTY_FUNCTION__);
        return -1;
    }
    trace_close();

    return 0;
}