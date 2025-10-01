#pragma once

#include <atomic>
#include <condition_variable>
#include <functional>
#include <future>
#include <mutex>
#include <queue>
#include <stdexcept>
#include <stop_token>
#include <thread>
#include <vector>

/**
 * @class ThreadPool
 * @brief 一个现代化的、使用 C++20 特性 (jthread, stop_token) 的线程池。
 */
class ThreadPool {
public:
    explicit ThreadPool(size_t thread_count = std::thread::hardware_concurrency())
    {
        if (thread_count == 0) {
            thread_count = 1;
        }

        workers_.reserve(thread_count);
        for (size_t i = 0; i < thread_count; ++i) {
            workers_.emplace_back([this](std::stop_token st) {
                while (true) {
                    std::function<void()> task;
                    {
                        std::unique_lock lock(queue_mutex_);
                        cv_.wait(lock, st, [this] { return !tasks_.empty(); });

                        if (tasks_.empty()) {
                            return;
                        }

                        task = std::move(tasks_.front());
                        tasks_.pop();
                    }

                    try {
                        task();
                    } catch (...) {
                        // 用户可通过 future.get() 获取异常
                    }
                }
            });
        }
    }

    ~ThreadPool() noexcept
    {
        shutdown();
    }

    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;

    ThreadPool(ThreadPool&& other) noexcept
        : workers_(std::move(other.workers_))
        , tasks_(std::move(other.tasks_))
        , shutdown_(other.shutdown_.load())
    {
        other.shutdown_.store(true);
    }

    ThreadPool& operator=(ThreadPool&& other) noexcept
    {
        if (this != &other) {
            shutdown();

            workers_ = std::move(other.workers_);
            tasks_ = std::move(other.tasks_);
            shutdown_.store(other.shutdown_.load()); // [微调] 使用 store 和 load

            other.shutdown_.store(true);
        }
        return *this;
    }

    template <typename F, typename... Args>
    auto enqueue(F&& f, Args&&... args)
        -> std::future<std::invoke_result_t<std::decay_t<F>, std::decay_t<Args>...>>
    {
        using return_type = std::invoke_result_t<std::decay_t<F>, std::decay_t<Args>...>;

        auto task = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...));

        std::future<return_type> res = task->get_future();

        {
            std::scoped_lock lock(queue_mutex_);
            if (shutdown_.load()) {
                throw std::runtime_error("ThreadPool is shutdown, cannot enqueue new tasks.");
            }
            tasks_.emplace([t = std::move(task)]() { (*t)(); });
        }

        cv_.notify_one();
        return res;
    }

private:
    void shutdown() noexcept
    {
        bool already_shutdown = shutdown_.exchange(true);
        if (already_shutdown) {
            return;
        }

        for (auto& worker : workers_) {
            worker.request_stop();
        }
        cv_.notify_all();

        workers_.clear(); // 析构并 join 所有 jthread
    }

    std::vector<std::jthread> workers_;
    std::queue<std::function<void()>> tasks_;

    std::mutex queue_mutex_;
    std::condition_variable_any cv_;

    std::atomic<bool> shutdown_ { false };
};