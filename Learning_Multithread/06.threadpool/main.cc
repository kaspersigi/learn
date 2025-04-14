#include <condition_variable>
#include <functional>
#include <mutex>
#include <print>
#include <queue>
#include <thread>
#include <vector>

class SimpleThreadPool {
public:
    explicit SimpleThreadPool(size_t thread_count)
        : stop(false)
    {
        for (size_t i = 0; i < thread_count; ++i) {
            workers.emplace_back([this] {
                while (true) {
                    std::function<void()> task;
                    {
                        std::unique_lock lock(queue_mutex);
                        condition.wait(lock, [this] {
                            return stop || !tasks.empty();
                        });

                        if (stop && tasks.empty())
                            return;

                        task = std::move(tasks.front());
                        tasks.pop();
                    }
                    task();
                }
            });
        }
    }

    template <typename F>
    void enqueue(F&& f)
    {
        {
            std::unique_lock lock(queue_mutex);
            tasks.emplace(std::forward<F>(f));
        }
        condition.notify_one();
    }

    ~SimpleThreadPool()
    {
        {
            std::unique_lock lock(queue_mutex);
            stop = true;
        }
        condition.notify_all();
        for (auto& worker : workers) {
            worker.join();
        }
    }

private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;

    std::mutex queue_mutex;
    std::condition_variable condition;
    bool stop = false;
};

auto main(int argc, char* argv[]) -> int
{
    std::print("Hello World!");

    return 0;
}