#define _POSIX_C_SOURCE 200809L

#include "threadpool.h"
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const int NUMBER = 2;

// 任务结构体
typedef struct Task {
    void* (*function)(void* arg);
    void* arg;
} Task;

// 线程池结构体
typedef struct ThreadPool {
    // 任务队列
    Task* task_q;

    int queue_capacity; // 容量
    int queue_size; // 当前任务个数
    int queue_front; // 队头 -> 取数据
    int queue_rear; // 队尾 -> 放数据

    pthread_t manager_tid; // 管理者线程ID
    pthread_t* thread_tids_p; // 工作的线程ID
    int min_num; // 最小线程数量
    int max_num; // 最大线程数量
    int busy_num; // 忙的线程的个数
    int live_num; // 存活的线程的个数
    int exit_num; // 要销毁的线程个数
    pthread_mutex_t mutex_pool; // 锁整个的线程池
    pthread_mutex_t mutex_busy; // 锁busy_num变量(它经常变，所以单独设计一个锁，以免每次都锁整个线程池)
    pthread_cond_t not_full; // 任务队列是不是满了
    pthread_cond_t not_empty; // 任务队列是不是空了

    bool is_destroy; // 是不是要销毁线程池, 销毁为1, 不销毁为0

} ThreadPool;

// 工作线程退出函数
void thread_exit(ThreadPool* threadpool_p);

// 工作线程函数
void* worker_f(void* arg);

// 管理者线程函数
void* manager_f(void* arg);

void thread_exit(ThreadPool* threadpool_p)
{
    pthread_t tid = pthread_self();
    for (int i = 0; i < threadpool_p->max_num; ++i) {
        if (threadpool_p->thread_tids_p[i] == tid) {
            threadpool_p->thread_tids_p[i] == 0;
            printf("%s: %s, pid: %d, tid: %lx, exiting...\n", __PRETTY_FUNCTION__, "worker thread", getpid(), tid);
            break;
        }
    }
    pthread_exit(NULL);
}

void* worker_f(void* arg)
{
    ThreadPool* threadpool_p = (ThreadPool*)arg;
    while (1) {
        pthread_mutex_trylock(&(threadpool_p->mutex_pool));
        // 当前任务队列是否为空
        while (0 == threadpool_p->queue_size && !threadpool_p->is_destroy) {
            // 阻塞工作线程
            pthread_cond_wait(&(threadpool_p->not_empty), &(threadpool_p->mutex_pool));

            // 判断是不是要销毁线程
            if (threadpool_p->exit_num > 0) {
                threadpool_p->exit_num--;
                if (threadpool_p->live_num > threadpool_p->min_num) {
                    threadpool_p->live_num--;
                    pthread_mutex_unlock(&(threadpool_p->mutex_pool));
                    thread_exit(threadpool_p);
                }
            }
        }
        // 判断线程池是否被关闭了
        if (threadpool_p->is_destroy) {
            pthread_mutex_unlock(&(threadpool_p->mutex_pool));
            thread_exit(threadpool_p);
        }
        // 从任务队列中取出一个任务
        Task task;
        task.function = threadpool_p->task_q[threadpool_p->queue_front].function;
        task.arg = threadpool_p->task_q[threadpool_p->queue_front].arg;
        // 移动环形队列头指针
        threadpool_p->queue_front = (threadpool_p->queue_front + 1) % threadpool_p->queue_capacity;
        threadpool_p->queue_size--;

        // 解锁
        pthread_cond_signal(&(threadpool_p->not_full));
        pthread_mutex_unlock(&(threadpool_p->mutex_pool));

        // 执行任务
        printf("%s: %s, pid: %d, tid: %lx, start working...\n", __PRETTY_FUNCTION__, "worker thread", getpid(), pthread_self());
        pthread_mutex_trylock(&(threadpool_p->mutex_busy));
        threadpool_p->busy_num++;
        task.function(task.arg);
        free(task.arg);
        pthread_mutex_unlock(&(threadpool_p->mutex_busy));

        // 任务执行完毕
        printf("%s: %s, pid: %d, tid: %lx, end working...\n", __PRETTY_FUNCTION__, "worker thread", getpid(), pthread_self());
        pthread_mutex_trylock(&(threadpool_p->mutex_busy));
        threadpool_p->busy_num--;
        pthread_mutex_unlock(&(threadpool_p->mutex_busy));
    }
    return NULL;
}

void* manager_f(void* arg)
{
    ThreadPool* threadpool_p = (ThreadPool*)arg;
    while (!threadpool_p->is_destroy) {
        // 管理者线程不需要不停的检测
        sleep(3);
        // 取出线程池中任务的数量和当前线程的数量
        pthread_mutex_trylock(&(threadpool_p->mutex_pool));
        int queue_size = threadpool_p->queue_size;
        int live_num = threadpool_p->live_num;
        pthread_mutex_unlock(&(threadpool_p->mutex_pool));

        // 取出忙的线程的数量
        pthread_mutex_trylock(&(threadpool_p->mutex_busy));
        int busy_num = threadpool_p->busy_num;
        pthread_mutex_unlock(&(threadpool_p->mutex_busy));

        // 添加线程
        // 可以有很多方案，这里举个例子
        // 任务的个数 > 存活的线程个数 && 存活的线程数 < 最大线程池
        if (queue_size > live_num && live_num < threadpool_p->max_num) {
            pthread_mutex_trylock(&(threadpool_p->mutex_pool));
            int counter = 0;
            for (int i = 0; i < threadpool_p->max_num && counter < NUMBER && threadpool_p->live_num < threadpool_p->max_num; ++i) {
                if (threadpool_p->thread_tids_p[i] == 0) {
                    pthread_create(&threadpool_p->thread_tids_p[i], NULL, worker_f, (void*)threadpool_p);
                    counter++;
                    threadpool_p->live_num++;
                }
            }
            pthread_mutex_unlock(&(threadpool_p->mutex_pool));
        }

        // 销毁线程
        // 可以有很多方案，这里举个例子
        // 忙的线程数*2 < 存活的线程数 && 存活的线程 > 最小线程数
        if (busy_num * 2 < live_num && live_num > threadpool_p->min_num) {
            pthread_mutex_trylock(&(threadpool_p->mutex_pool));
            threadpool_p->exit_num = NUMBER;
            pthread_mutex_unlock(&(threadpool_p->mutex_pool));

            // 让工作线程自杀
            for (int i = 0; i < NUMBER; ++i) {
                pthread_cond_signal(&(threadpool_p->not_empty));
            }
        }
    }

    return NULL;
}

ThreadPool* threadpool_create(int min, int max, int capacity)
{
    ThreadPool* threadpool_p = (ThreadPool*)malloc(sizeof(ThreadPool));

    do {
        if (NULL == threadpool_p) {
            fputs("malloc threadpool failed...\n", stderr);
            // return NULL;
            break;
        }
        threadpool_p->min_num = min;
        threadpool_p->max_num = max;
        threadpool_p->queue_capacity = capacity;
        threadpool_p->thread_tids_p = (pthread_t*)malloc(max * sizeof(pthread_t));
        if (NULL == threadpool_p->thread_tids_p) {
            fputs("malloc thread_tids_p failed...\n", stderr);
            // return NULL;
            break;
        }
        memset(threadpool_p->thread_tids_p, 0, max * sizeof(pthread_t));

        threadpool_p->busy_num = 0;
        threadpool_p->live_num = min; // 和最小个数相等
        threadpool_p->exit_num = 0;

        if (pthread_mutex_init(&threadpool_p->mutex_pool, NULL) != 0 || pthread_mutex_init(&threadpool_p->mutex_busy, NULL) != 0 || pthread_cond_init(&threadpool_p->not_empty, NULL) != 0 || pthread_cond_init(&threadpool_p->not_full, NULL) != 0) {
            fputs("mutex or condition init fail...\n", stderr);
        }

        // 任务队列
        threadpool_p->task_q = (Task*)malloc(capacity * sizeof(Task));
        threadpool_p->queue_size = 0;
        threadpool_p->queue_front = 0;
        threadpool_p->queue_rear = 0;

        threadpool_p->is_destroy = false;

        // 创建线程
        pthread_create(&(threadpool_p->manager_tid), NULL, manager_f, (void*)threadpool_p);
        printf("%s: %s, pid: %d, tid: %lx, is creating...\n", __PRETTY_FUNCTION__, "manage thread", getpid(), threadpool_p->manager_tid);

        for (int i = 0; i < min; ++i) {
            pthread_create(&(threadpool_p->thread_tids_p[i]), NULL, worker_f, (void*)threadpool_p);
            printf("%s: %s, pid: %d, tid: %lx, is creating...\n", __PRETTY_FUNCTION__, "work thread", getpid(), threadpool_p->thread_tids_p[i]);
        }
        return threadpool_p;
    } while (0);

    // 释放资源
    if (threadpool_p && threadpool_p->thread_tids_p) {
        free(threadpool_p->thread_tids_p);
    }
    if (threadpool_p && threadpool_p->task_q) {
        free(threadpool_p->task_q);
    }
    if (threadpool_p) {
        free(threadpool_p);
    }

    return NULL;
}

int threadpool_destroy(ThreadPool* threadpool_p)
{
    if (threadpool_p == NULL)
        return -1;
    else {
        // 关闭线程池
        threadpool_p->is_destroy = true;
        // 阻塞回收管理者线程
        pthread_join(threadpool_p->manager_tid, NULL);
        // 唤醒阻塞的消费者线程
        for (int i = 0; i < threadpool_p->live_num; ++i) {
            pthread_cond_signal(&(threadpool_p->not_empty));
        }

        sleep(1);

        // 释放堆内存
        if (NULL != threadpool_p->task_q) {
            free(threadpool_p->task_q);
        }
        threadpool_p->task_q = NULL;

        if (NULL != threadpool_p->thread_tids_p) {
            free(threadpool_p->thread_tids_p);
        }
        threadpool_p->thread_tids_p = NULL;

        pthread_cond_destroy(&(threadpool_p->not_empty));
        pthread_cond_destroy(&(threadpool_p->not_full));
        pthread_mutex_destroy(&(threadpool_p->mutex_busy));
        pthread_mutex_destroy(&(threadpool_p->mutex_pool));

        free(threadpool_p);
        threadpool_p = NULL;

        return 0;
    }
}

void threadpool_add(ThreadPool* threadpool_p, void* (*function)(void* arg), void* arg)
{
    pthread_mutex_trylock(&(threadpool_p->mutex_pool));
    while (threadpool_p->queue_size == threadpool_p->queue_capacity && !threadpool_p->is_destroy) {
        // 阻塞生产者线程
        pthread_cond_wait(&(threadpool_p->not_full), &(threadpool_p->mutex_pool));
    }
    if (threadpool_p->is_destroy) {
        pthread_mutex_unlock(&(threadpool_p->mutex_pool));
        return;
    }
    printf("%s: %s, pid: %d, tid: %lx, task adding...\n", __PRETTY_FUNCTION__, "main thread", getpid(), pthread_self());

    // 添加任务
    threadpool_p->task_q[threadpool_p->queue_rear].function = function;
    threadpool_p->task_q[threadpool_p->queue_rear].arg = arg;

    // 移动环形队列尾指针
    threadpool_p->queue_rear = (threadpool_p->queue_rear + 1) % threadpool_p->queue_capacity;
    threadpool_p->queue_size++;

    pthread_cond_signal(&(threadpool_p->not_empty));
    pthread_mutex_unlock(&(threadpool_p->mutex_pool));
}

int threadpool_busy_number(ThreadPool* threadpool_p)
{
    if (threadpool_p->is_destroy)
        return 0;
    else {
        int working_number;
        pthread_mutex_trylock(&(threadpool_p->mutex_busy));
        working_number = threadpool_p->busy_num;
        pthread_mutex_unlock(&(threadpool_p->mutex_busy));
        return working_number;
    }
}

int threadpool_live_number(ThreadPool* threadpool_p)
{
    if (threadpool_p->is_destroy)
        return 0;
    else {
        int working_number;
        pthread_mutex_trylock(&(threadpool_p->mutex_pool));
        working_number = threadpool_p->live_num;
        pthread_mutex_unlock(&(threadpool_p->mutex_pool));
        return working_number;
    }
}