#pragma once

typedef struct ThreadPool ThreadPool;

// 创建线程池并初始化
ThreadPool* threadpool_create(int min, int max, int capacity);

// 销毁线程池
int threadpool_destroy(ThreadPool* threadpool_p);

// 给线程池添加任务
void threadpool_add(ThreadPool* threadpool_p, void* (*function)(void* arg), void* arg);

// 获取线程池中工作的线程的个数
int threadpool_busy_number(ThreadPool* threadpool_p);

// 获取线程池中活着的线程的个数
int threadpool_live_number(ThreadPool* threadpool_p);