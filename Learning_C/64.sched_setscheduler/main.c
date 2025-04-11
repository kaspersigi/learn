#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE
#include "ftrace.h"
#include <sched.h>

void* func(void* arg)
{
    trace_dur_begin("ChildThread");
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