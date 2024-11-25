#pragma once

#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

typedef void* (*callback)(void* arg);

class Task {
public:
    Task();
    Task(callback function, void* arg);
    ~Task();
    callback _function;
    void* _arg;
};

class TaskQueue {
public:
    TaskQueue();
    ~TaskQueue();
    void push_task(callback function, void* arg);
    Task pop_task();
    size_t size();
    bool is_empty();

private:
    std::queue<Task> _task_queue;
    std::mutex _mutex;
};

class ThreadPool {
public:
    ThreadPool(int min = 5, int max = 10);
    ~ThreadPool();
    bool is_close();
    void add_task(callback function = nullptr, void* arg = nullptr);
    int get_busy_num();
    int get_alive_num();

private:
    TaskQueue _task_queue;
    std::mutex _mutex;
    std::condition_variable _cond_worker;
    std::condition_variable _cond_manager;
    int _min_num;
    int _max_num;
    int _busy_num;
    int _alive_num;
    int _exit_num;
    bool _is_close;
    std::vector<std::thread> _thread_v;
    void _manager();
    void _worker();
};