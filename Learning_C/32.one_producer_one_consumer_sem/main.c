#define _POSIX_C_SOURCE 200809L

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

const int MAX = 5;
sem_t remain, apple, mutex;
static unsigned int vremain = MAX, vapple = 0;

void show(const char* fun_name)
{
    printf("%s say: cost = %d, remain = %d\n", fun_name, vapple, vremain);
}

void* fn_producer(void*)
{
    while (1) {
        sem_wait(&remain);
        sem_wait(&mutex);
        vremain--;
        vapple++;
        // show(__PRETTY_FUNCTION__);
        sem_post(&mutex);
        sem_post(&apple);
        sleep(2);
    }
    return (void*)0;
}

void* fn_consumer(void*)
{
    while (1) {
        sem_wait(&apple);
        sem_wait(&mutex);
        vapple--;
        vremain++;
        // show(__PRETTY_FUNCTION__);
        sem_post(&mutex);
        sem_post(&remain);
        sleep(3);
    }
    return (void*)0;
}

int main(int argc, char* argv[])
{
    pid_t pid = getpid();
    pthread_t tid_main = pthread_self();
    pthread_t tid_producer, tid_consumer;

    sem_init(&remain, 0, MAX);
    sem_init(&apple, 0, 0);
    sem_init(&mutex, 0, 1);

    show(__PRETTY_FUNCTION__);

    pthread_create(&tid_producer, NULL, fn_producer, NULL);
    pthread_create(&tid_consumer, NULL, fn_consumer, NULL);

    printf("pid: %d\n", pid);
    printf("tid_main: %lx\n", tid_main);
    printf("tid_producer: %lx\n", tid_producer);
    printf("tid_consumer: %lx\n", tid_consumer);

    while (1) {
        sem_wait(&mutex);
        show(__PRETTY_FUNCTION__);
        sem_post(&mutex);
        sleep(1);
    }

    return 0;
}