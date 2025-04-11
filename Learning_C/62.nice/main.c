#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE
#include "ftrace.h"
#include <errno.h>

void* func(void* arg)
{
    trace_dur_begin("ChildThread");
    printf("child thread nice = %d\n", nice(0));
    int new_nice = nice(-10);
    if (-1 == new_nice && 0 != errno) {
        perror("child thread nice() failed");
        return (void*)-1;
    } else {
        printf("child thread new_nice = %d\n", new_nice);
    }
    printf("child thread nice = %d\n", nice(0));
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
    printf("main thread nice = %d\n", nice(0));
    ret = pthread_create(&tid, NULL, func, NULL);
    if (0 != ret) {
        printf("create new thread failed!\n");
        return -1;
    }
    pthread_join(tid, NULL);
    printf("main thread nice = %d\n", nice(0));

    ret = trace_dur_end();
    if (ret <= 0) {
        printf("%s: trace_dur_end filed!\n", __PRETTY_FUNCTION__);
        return -1;
    }
    trace_close();

    return 0;
}