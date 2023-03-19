#define _POSIX_C_SOURCE 200809L

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t mutex;
pthread_cond_t cond_producer;
pthread_cond_t cond_consumer;
static const int size = 5;
int count = 0;

void* producer(void* arg)
{
    while (1) {
        pthread_mutex_lock(&mutex);
        while (count == size || count + 2 > size) {
            pthread_cond_wait(&cond_producer, &mutex);
        }
        count += 2;
        printf("producer produces one product, count = %d\n", count);
        pthread_mutex_unlock(&mutex);
        pthread_cond_broadcast(&cond_consumer);
        sleep(1);
    }
    return NULL;
}

void* consumer(void* arg)
{
    while (1) {
        pthread_mutex_lock(&mutex);
        while (count == 0) {
            pthread_cond_wait(&cond_consumer, &mutex);
        }
        --count;
        printf("consumer consumes one product, count = %d\n", count);
        pthread_mutex_unlock(&mutex);
        pthread_cond_broadcast(&cond_producer);
        sleep(1);
    }
    return NULL;
}

int main(int argc, char* argv[])
{
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond_producer, NULL);
    pthread_cond_init(&cond_consumer, NULL);
    pthread_t thread_producer1, thread_consumer1, thread_producer2, thread_consumer2;
    pthread_create(&thread_producer1, NULL, producer, NULL);
    pthread_create(&thread_consumer1, NULL, consumer, NULL);
    pthread_create(&thread_producer2, NULL, producer, NULL);
    pthread_create(&thread_consumer2, NULL, consumer, NULL);
    pthread_join(thread_producer1, NULL);
    pthread_join(thread_consumer1, NULL);
    pthread_join(thread_producer2, NULL);
    pthread_join(thread_consumer2, NULL);
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond_producer);
    pthread_cond_destroy(&cond_consumer);
    return 0;
}