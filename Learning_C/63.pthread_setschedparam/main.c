#define _POSIX_C_SOURCE 200809L
#include "ftrace.h"
#include <sched.h>
#include <stdio.h>
#include <unistd.h>

void* func(void* arg)
{
    ftrace_duration_begin("ChildThread");
    pthread_t tid = pthread_self();
    int old_prio, new_prio, current_prio;
    int old_policy, new_policy, current_policy;
    struct sched_param old_param, new_param, current_param;

    if (pthread_getschedparam(tid, &old_policy, &old_param) != 0) {
        perror("pthread_getschedparam");
        return (void*)-1;
    } else {
        printf("old_policy = %d, old_prio = %d\n", old_policy, old_param.sched_priority);
    }

    new_policy = SCHED_RR;
    new_param.sched_priority = sched_get_priority_min(new_policy);
    if (pthread_setschedparam(tid, new_policy, &new_param) != 0) {
        perror("pthread_setschedparam");
        return (void*)-1;
    }

    if (pthread_getschedparam(tid, &current_policy, &current_param) != 0) {
        perror("pthread_getschedparam");
        return (void*)-1;
    } else {
        printf("current_policy = %d, current_prio = %d\n", current_policy, current_param.sched_priority);
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