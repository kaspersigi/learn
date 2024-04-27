#define _POSIX_C_SOURCE 200809L

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

const int MAX = 5;
sem_t remain, apple, orange, mutex;
static unsigned int vremain = MAX, vapple = 0, vorange = 0;

void show(const char* fun_name)
{
    printf("%s say: apple = %d, orange = %d, remain = %d\n", fun_name, vorange, vapple, vremain);
}

void* fn_producer1(void*)
{
    while (1) {
        sem_wait(&remain);
        sem_wait(&mutex);
        vremain--;
        vapple++;
        // show(__PRETTY_FUNCTION__);
        sem_post(&mutex);
        sem_post(&apple);
        sleep(1);
    }
    return (void*)0;
}

void* fn_producer2(void*)
{
    while (1) {
        sem_wait(&remain);
        sem_wait(&mutex);
        vremain--;
        vorange++;
        // show(__PRETTY_FUNCTION__);
        sem_post(&mutex);
        sem_post(&orange);
        sleep(1);
    }
    return (void*)0;
}

void* fn_consumer1(void*)
{
    while (1) {
        sem_wait(&apple);
        sem_wait(&mutex);
        vapple--;
        vremain++;
        // show(__PRETTY_FUNCTION__);
        sem_post(&mutex);
        sem_post(&remain);
        sleep(2);
    }
    return (void*)0;
}

void* fn_consumer2(void*)
{
    while (1) {
        sem_wait(&orange);
        sem_wait(&mutex);
        vorange--;
        vremain++;
        // show(__PRETTY_FUNCTION__);
        sem_post(&mutex);
        sem_post(&remain);
        sleep(2);
    }
    return (void*)0;
}

int main(int argc, char* argv[])
{
    pid_t pid = getpid();
    pthread_t tid_main = pthread_self();
    pthread_t tid_producer1, tid_producer2, tid_consumer1, tid_consumer2;

    sem_init(&remain, 0, MAX);
    sem_init(&apple, 0, 0);
    sem_init(&orange, 0, 0);
    sem_init(&mutex, 0, 1);

    show(__PRETTY_FUNCTION__);

    pthread_create(&tid_producer1, NULL, fn_producer1, NULL);
    pthread_create(&tid_producer2, NULL, fn_producer2, NULL);
    pthread_create(&tid_consumer1, NULL, fn_consumer1, NULL);
    pthread_create(&tid_consumer2, NULL, fn_consumer2, NULL);

    printf("pid: %d\n", pid);
    printf("tid_main: %lx\n", tid_main);
    printf("tid_producer1: %lx\n", tid_producer1);
    printf("tid_producer2: %lx\n", tid_producer2);
    printf("tid_consumer1: %lx\n", tid_consumer1);
    printf("tid_consumer2: %lx\n", tid_consumer2);

    while (1) {
        sem_wait(&mutex);
        show(__PRETTY_FUNCTION__);
        sem_post(&mutex);
        sleep(1);
    }

    return 0;
}