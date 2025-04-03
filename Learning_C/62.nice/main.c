#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void* func(void* arg)
{
    printf("child thread nice = %d\n", nice(0));
    int new_nice = nice(-10);
    if (-1 == new_nice && 0 != errno) {
        perror("child thread nice() failed");
        return (void*)-1;
    } else {
        printf("child thread new_nice = %d\n", new_nice);
    }
    printf("child thread nice = %d\n", nice(0));

    return (void*)0;
}

int main(int argc, char* argv[])
{
    pthread_t tid;
    printf("main thread nice = %d\n", nice(0));
    int ret = pthread_create(&tid, NULL, func, NULL);
    if (0 != ret) {
        printf("create new thread failed!\n");
        return -1;
    }
    pthread_join(tid, NULL);
    printf("main thread nice = %d\n", nice(0));

    return 0;
}