#define _POSIX_C_SOURCE 200809L
#include "ftrace.h"
#include <sched.h>

void* func(void* arg)
{
    trace_dur_begin("ChildThread");
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