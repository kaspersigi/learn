#define _POSIX_C_SOURCE 200809L

#include "threadpool.h"
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// 每次扩缩容的线程数量
#define SCALE_STEP 2

// 任务结构体
typedef struct Task {
    void* (*function)(void* arg);
    void* arg;
} Task;

// 线程池结构体
struct ThreadPool {
    Task* task_q;
    int queue_capacity;
    int queue_size;
    int queue_front;
    int queue_rear;

    pthread_t manager_tid;
    pthread_t* thread_tids_p;
    int min_num;
    int max_num;
    int busy_num;
    int live_num;
    int exit_num;

    pthread_mutex_t mutex_pool;
    pthread_mutex_t mutex_busy;
    pthread_cond_t not_full;
    pthread_cond_t not_empty;

    bool is_destroy;
};

// 工作线程函数
static void* worker_f(void* arg);

// 管理者线程函数
static void* manager_f(void* arg);

static void* worker_f(void* arg)
{
    ThreadPool* pool = (ThreadPool*)arg;
    while (1) {
        Task task;
        bool should_exit = false;

        // 获取锁，检查任务或退出条件
        pthread_mutex_lock(&pool->mutex_pool);

        // 等待任务或销毁信号
        while (pool->queue_size == 0 && !pool->is_destroy) {
            pthread_cond_wait(&pool->not_empty, &pool->mutex_pool);
        }

        // 如果线程池被销毁，退出
        if (pool->is_destroy) {
            pthread_mutex_unlock(&pool->mutex_pool);
            break;
        }

        // 检查是否需要自杀（由管理者触发）
        if (pool->exit_num > 0 && pool->live_num > pool->min_num) {
            pool->exit_num--;
            pool->live_num--;
            pthread_mutex_unlock(&pool->mutex_pool);
            break;
        }

        // 取出任务
        task.function = pool->task_q[pool->queue_front].function;
        task.arg = pool->task_q[pool->queue_front].arg;
        pool->queue_front = (pool->queue_front + 1) % pool->queue_capacity;
        pool->queue_size--;

        pthread_cond_signal(&pool->not_full);
        pthread_mutex_unlock(&pool->mutex_pool);

        // 执行任务
        pthread_mutex_lock(&pool->mutex_busy);
        pool->busy_num++;
        pthread_mutex_unlock(&pool->mutex_busy);

        task.function(task.arg); // 用户负责管理 arg 生命周期

        pthread_mutex_lock(&pool->mutex_busy);
        pool->busy_num--;
        pthread_mutex_unlock(&pool->mutex_busy);
    }

    // 清理 thread_tids_p 中的 tid
    pthread_t tid = pthread_self();
    pthread_mutex_lock(&pool->mutex_pool);
    for (int i = 0; i < pool->max_num; ++i) {
        if (pool->thread_tids_p[i] == tid) {
            pool->thread_tids_p[i] = 0; // 修复：赋值而非比较
            break;
        }
    }
    pthread_mutex_unlock(&pool->mutex_pool);

    return NULL;
}

static void* manager_f(void* arg)
{
    ThreadPool* pool = (ThreadPool*)arg;
    while (!pool->is_destroy) {
        sleep(3); // 管理者每3秒检查一次（简单实现）

        int queue_size, live_num, busy_num;

        pthread_mutex_lock(&pool->mutex_pool);
        queue_size = pool->queue_size;
        live_num = pool->live_num;
        pthread_mutex_unlock(&pool->mutex_pool);

        pthread_mutex_lock(&pool->mutex_busy);
        busy_num = pool->busy_num;
        pthread_mutex_unlock(&pool->mutex_busy);

        // 扩容：任务多且线程未达上限
        if (queue_size > live_num && live_num < pool->max_num) {
            pthread_mutex_lock(&pool->mutex_pool);
            int counter = 0;
            for (int i = 0; i < pool->max_num && counter < SCALE_STEP && pool->live_num < pool->max_num; ++i) {
                if (pool->thread_tids_p[i] == 0) {
                    if (pthread_create(&pool->thread_tids_p[i], NULL, worker_f, pool) == 0) {
                        counter++;
                        pool->live_num++;
                    }
                }
            }
            pthread_mutex_unlock(&pool->mutex_pool);
        }

        // 缩容：空闲线程过多
        if (busy_num * 2 < live_num && live_num > pool->min_num) {
            pthread_mutex_lock(&pool->mutex_pool);
            int to_exit = live_num - pool->min_num;
            pool->exit_num = (to_exit > SCALE_STEP) ? SCALE_STEP : to_exit;
            pthread_mutex_unlock(&pool->mutex_pool);

            for (int i = 0; i < pool->exit_num; ++i) {
                pthread_cond_signal(&pool->not_empty);
            }
        }
    }
    return NULL;
}

ThreadPool* threadpool_create(int min, int max, int capacity)
{
    // 参数验证
    if (min <= 0 || max <= 0 || capacity <= 0 || min > max) {
        return NULL;
    }

    ThreadPool* pool = (ThreadPool*)malloc(sizeof(ThreadPool));
    if (!pool)
        return NULL;

    // 初始化基本字段
    pool->min_num = min;
    pool->max_num = max;
    pool->queue_capacity = capacity;
    pool->queue_size = 0;
    pool->queue_front = 0;
    pool->queue_rear = 0;
    pool->busy_num = 0;
    pool->live_num = min;
    pool->exit_num = 0;
    pool->is_destroy = false;

    // 分配线程ID数组
    pool->thread_tids_p = (pthread_t*)calloc(max, sizeof(pthread_t));
    if (!pool->thread_tids_p) {
        free(pool);
        return NULL;
    }

    // 分配任务队列
    pool->task_q = (Task*)malloc(capacity * sizeof(Task));
    if (!pool->task_q) {
        free(pool->thread_tids_p);
        free(pool);
        return NULL;
    }

    // 初始化同步原语
    if (pthread_mutex_init(&pool->mutex_pool, NULL) != 0 || pthread_mutex_init(&pool->mutex_busy, NULL) != 0 || pthread_cond_init(&pool->not_empty, NULL) != 0 || pthread_cond_init(&pool->not_full, NULL) != 0) {
        free(pool->task_q);
        free(pool->thread_tids_p);
        free(pool);
        return NULL;
    }

    // 创建管理者线程
    if (pthread_create(&pool->manager_tid, NULL, manager_f, pool) != 0) {
        goto cleanup;
    }

    // 创建初始工作线程
    for (int i = 0; i < min; ++i) {
        if (pthread_create(&pool->thread_tids_p[i], NULL, worker_f, pool) != 0) {
            // 创建失败，标记销毁并清理
            pool->is_destroy = true;
            pthread_cond_broadcast(&pool->not_empty);
            pthread_join(pool->manager_tid, NULL);
            for (int j = 0; j < i; ++j) {
                pthread_join(pool->thread_tids_p[j], NULL);
            }
            goto cleanup;
        }
    }

    return pool;

cleanup:
    pthread_mutex_destroy(&pool->mutex_pool);
    pthread_mutex_destroy(&pool->mutex_busy);
    pthread_cond_destroy(&pool->not_empty);
    pthread_cond_destroy(&pool->not_full);
    free(pool->task_q);
    free(pool->thread_tids_p);
    free(pool);
    return NULL;
}

int threadpool_destroy(ThreadPool* pool)
{
    if (!pool)
        return -1;

    // 1. 标记销毁
    pthread_mutex_lock(&pool->mutex_pool);
    pool->is_destroy = true;
    pthread_mutex_unlock(&pool->mutex_pool);

    // 2. 唤醒所有等待线程
    pthread_cond_broadcast(&pool->not_empty);
    pthread_cond_broadcast(&pool->not_full);

    // 3. join 管理者线程
    pthread_join(pool->manager_tid, NULL);

    // 4. join 所有工作线程
    for (int i = 0; i < pool->max_num; ++i) {
        if (pool->thread_tids_p[i] != 0) {
            pthread_join(pool->thread_tids_p[i], NULL);
        }
    }

    // 5. 清理资源
    free(pool->task_q);
    free(pool->thread_tids_p);
    pthread_mutex_destroy(&pool->mutex_pool);
    pthread_mutex_destroy(&pool->mutex_busy);
    pthread_cond_destroy(&pool->not_empty);
    pthread_cond_destroy(&pool->not_full);
    free(pool);

    return 0;
}

void threadpool_add(ThreadPool* pool, void* (*function)(void* arg), void* arg)
{
    if (!pool || !function)
        return;

    pthread_mutex_lock(&pool->mutex_pool);

    // 关键优化：销毁过程中拒绝新任务
    if (pool->is_destroy) {
        pthread_mutex_unlock(&pool->mutex_pool);
        return;
    }

    // 等待队列有空间
    while (pool->queue_size == pool->queue_capacity) {
        pthread_cond_wait(&pool->not_full, &pool->mutex_pool);
        // 再次检查是否被销毁
        if (pool->is_destroy) {
            pthread_mutex_unlock(&pool->mutex_pool);
            return;
        }
    }

    // 添加任务
    pool->task_q[pool->queue_rear].function = function;
    pool->task_q[pool->queue_rear].arg = arg;
    pool->queue_rear = (pool->queue_rear + 1) % pool->queue_capacity;
    pool->queue_size++;

    pthread_cond_signal(&pool->not_empty);
    pthread_mutex_unlock(&pool->mutex_pool);
}

int threadpool_busy_number(ThreadPool* pool)
{
    if (!pool || pool->is_destroy)
        return 0;
    int busy;
    pthread_mutex_lock(&pool->mutex_busy);
    busy = pool->busy_num;
    pthread_mutex_unlock(&pool->mutex_busy);
    return busy;
}

int threadpool_live_number(ThreadPool* pool)
{
    if (!pool || pool->is_destroy)
        return 0;
    int live;
    pthread_mutex_lock(&pool->mutex_pool);
    live = pool->live_num;
    pthread_mutex_unlock(&pool->mutex_pool);
    return live;
}