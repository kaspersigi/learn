#pragma once

#include <condition_variable>
#include <functional>
#include <future>
#include <mutex>
#include <queue>
#include <stop_token>
#include <thread>
#include <vector>

class ThreadPool {
public:
    explicit ThreadPool(size_t thread_count = std::thread::hardware_concurrency())
    {
        workers.reserve(thread_count);
        for (size_t i = 0; i < thread_count; ++i) {
            workers.emplace_back([this](std::stop_token st) {
                while (!st.stop_requested()) {
                    std::function<void()> task;
                    {
                        std::unique_lock lock(queue_mutex);
                        cv.wait(lock, st, [this] { return !tasks.empty(); });

                        if (st.stop_requested() || tasks.empty()) {
                            return;
                        }

                        task = std::move(tasks.front());
                        tasks.pop();
                    }
                    task();
                }
            });
        }
    }

    ~ThreadPool()
    {
        for (auto& worker : workers) {
            worker.request_stop();
        }
        cv.notify_all();
        for (auto& worker : workers) {
            if (worker.joinable()) {
                worker.join();
            }
        }
    }

    // 修改 enqueue 函数，支持 std::future 返回
    template <typename F, typename... Args>
    auto enqueue(F&& f, Args&&... args) -> std::future<std::invoke_result_t<F, Args...>>
    {
        using return_type = std::invoke_result_t<F, Args...>;

        auto task = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...));

        std::future<return_type> res = task->get_future();

        {
            std::scoped_lock lock(queue_mutex);
            tasks.emplace([task]() { (*task)(); });
        }

        cv.notify_one();
        return res;
    }

private:
    std::vector<std::jthread> workers; // 使用 jthread 自动管理线程
    std::queue<std::function<void()>> tasks;

    std::mutex queue_mutex;
    std::condition_variable_any cv;
};