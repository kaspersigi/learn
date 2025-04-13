#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE
#include "ftrace.h"
#include <sched.h>
#include <stdio.h>
#include <unistd.h>

void* func(void* arg)
{
    ftrace_duration_begin("ChildThread");
    pid_t tid = gettid();
    int old_sched = sched_getscheduler(tid);
    if (-1 == old_sched) {
        perror("sched_getscheduler");
        return (void*)-1;
    } else {
        printf("old_sched = %d\n", old_sched);
    }

    int new_policy = SCHED_RR;
    struct sched_param new_param;
    new_param.sched_priority = sched_get_priority_min(new_policy);
    if (-1 == sched_setscheduler(tid, new_policy, &new_param)) {
        perror("sched_setscheduler");
        return (void*)-1;
    }

    int new_sched = sched_getscheduler(tid);
    if (-1 == new_sched) {
        perror("sched_getscheduler");
        return (void*)-1;
    } else {
        printf("new_sched = %d\n", new_sched);
    }
    ftrace_duration_end();

    return (void*)0;
}

int main(int argc, char* argv[])
{
    if (!ftrace_init()) {
        printf("%s: ftrace_init filed!\n", __PRETTY_FUNCTION__);
        return -1;
    }
    int ret = ftrace_duration_begin("MyFtrace");

    pthread_t tid;
    ret = pthread_create(&tid, NULL, func, NULL);
    if (0 != ret) {
        printf("create new thread failed!\n");
        return -1;
    }
    pthread_join(tid, NULL);

    ret = ftrace_duration_end();
    ftrace_close();

    return 0;
}