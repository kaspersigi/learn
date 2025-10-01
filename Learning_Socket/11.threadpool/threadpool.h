#pragma once

/**
 * @file threadpool.h
 * @brief 动态线程池（C11/C17 兼容）
 *
 * 特性：
 * - 动态扩缩容（最小/最大线程数）
 * - 管理者线程自动调整线程数量
 * - 环形任务队列
 * - 优雅关闭（执行完所有已提交任务）
 *
 * 注意：
 * - 用户必须保证任务参数 (arg) 的生命周期
 *   建议：在任务函数中 free(arg)
 * - 不支持 C++ 异常，任务崩溃会导致线程退出
 */

typedef struct ThreadPool ThreadPool;

/**
 * @brief 创建线程池
 * @param min 最小线程数（>0）
 * @param max 最大线程数（>=min）
 * @param capacity 任务队列容量（>0）
 * @return 成功返回线程池指针，失败返回 NULL
 */
ThreadPool* threadpool_create(int min, int max, int capacity);

/**
 * @brief 销毁线程池（阻塞直到所有任务完成）
 * @param pool 线程池指针
 * @return 0 成功，-1 失败
 */
int threadpool_destroy(ThreadPool* pool);

/**
 * @brief 提交任务到线程池
 * @param pool 线程池指针
 * @param function 任务函数（不可为 NULL）
 * @param arg 传递给任务函数的参数（生命周期由用户管理）
 *
 * 注意：如果线程池正在销毁或已销毁，任务将被丢弃
 */
void threadpool_add(ThreadPool* pool, void* (*function)(void* arg), void* arg);

/**
 * @brief 获取忙线程数量
 */
int threadpool_busy_number(ThreadPool* pool);

/**
 * @brief 获取存活线程数量
 */
int threadpool_live_number(ThreadPool* pool);