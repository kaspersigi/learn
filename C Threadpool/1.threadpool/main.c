#include "threadpool.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void* task_function(void* arg)
{
    sleep(1);
    printf("%s: %s, pid: %d, tid: %lx, task is working...\n", __PRETTY_FUNCTION__, "task function", getpid(), pthread_self());
    return NULL;
}

int main(int argc, char* argv[])
{
    printf("%s: %s, pid: %d, tid: %lx, is starting...\n", __PRETTY_FUNCTION__, "main thread", getpid(), pthread_self());
    ThreadPool* threadpool = threadpool_create(3, 10, 100);
    for (int i = 0; i < 10; ++i) {
        printf("%s: %s, pid: %d, tid: %lx, prepare adding task...\n", __PRETTY_FUNCTION__, "main thread", getpid(), pthread_self());
        threadpool_add(threadpool, task_function, NULL);
    }
    sleep(5);
    threadpool_destroy(threadpool);
    return 0;
}