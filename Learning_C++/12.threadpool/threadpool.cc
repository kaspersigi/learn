#include "threadpool.h"
#include <algorithm>

static const int number = 2;

Task::Task()
    : _function(nullptr)
    , _arg(nullptr)
{
}

Task::Task(callback function, void* arg)
    : _function(function)
    , _arg(arg)
{
}

Task::~Task()
{
    // free(_arg);
    // 不可使用delete(_arg)
    // 永远不要delete void*
    // 不会调用析构函数，会造成内存泄漏
}

TaskQueue::TaskQueue()
{
}
TaskQueue::~TaskQueue()
{
}

void TaskQueue::push_task(callback function, void* arg)
{
    _task_queue.push(Task(function, arg));
}

Task TaskQueue::pop_task()
{
    Task task = _task_queue.front();
    _task_queue.pop();
    return task;
}

size_t TaskQueue::size()
{
    return _task_queue.size();
}

bool TaskQueue::is_empty()
{
    return _task_queue.empty();
}

ThreadPool::ThreadPool(int min, int max)
    : _min_num(min)
    , _max_num(max)
    , _busy_num(0)
    , _alive_num(0)
    , _exit_num(0)
    , _is_close(false)
{
    _mutex.lock();
    std::cout << "create manager thread..." << std::endl;
    _thread_v.push_back(std::thread(&ThreadPool::_manager, this));

    for (int i = 0; i < min; ++i) {
        std::cout << "create worker thread..." << std::endl;
        _thread_v.push_back(std::thread(&ThreadPool::_worker, this));
    }
    _mutex.unlock();
}

ThreadPool::~ThreadPool()
{
    std::for_each(_thread_v.begin(), _thread_v.end(), [](auto& e) { e.join(); });
}

bool ThreadPool::is_close()
{
    return _is_close;
}

void ThreadPool::add_task(callback function, void* arg)
{
    _mutex.lock();
    std::cout << "adding task..." << std::endl;
    _task_queue.push_task(function, arg);
    _mutex.unlock();
    _cond_worker.notify_all();
}

int ThreadPool::get_busy_num()
{
    return _busy_num;
}

int ThreadPool::get_alive_num()
{
    return _alive_num;
}

void ThreadPool::_manager()
{
    while (!is_close()) {
        std::this_thread::sleep_for(std::chrono::seconds(3));
        _mutex.lock();
        int task_size = _task_queue.size();
        int alive_num = _alive_num;
        int busy_num = _busy_num;
        _mutex.unlock();
        // 任务的个数 > 存活的线程个数 && 存活的线程数 < 最大线程池
        if (task_size > alive_num && alive_num < _max_num) {
            _mutex.lock();
            int counter = 0;
            for (int i = 0; _max_num && counter < number && _alive_num < _max_num; ++i) {
                _thread_v.push_back(std::thread(&ThreadPool::_worker, this));
                counter++;
                _alive_num++;
            }
            _mutex.unlock();
        }
        if (busy_num * 2 < alive_num && alive_num > _min_num) {
            _mutex.lock();
            _exit_num = number;
            _mutex.unlock();
        }
    }
}

void ThreadPool::_worker()
{
    while (1) {
        std::unique_lock<std::mutex> ul(_mutex);
        _cond_worker.wait(ul, [&]() { return !_task_queue.is_empty(); });

        Task task = _task_queue.pop_task();
        std::cout << "worker thread : " << std::hex << std::this_thread::get_id() << " is doing..." << std::endl;
        task._function(task._arg);
        std::cout << "worker thread : " << std::hex << std::this_thread::get_id() << " is done..." << std::endl;
    }
}
