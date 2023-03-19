#include <atomic>
#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

std::mutex g_mutex;
std::condition_variable cond_producer;
std::condition_variable cond_consumer;
static const int size = 5;
std::atomic<int> count(0);

auto producer() -> void
{
    while (1) {
        {
            std::unique_lock<std::mutex> ul(g_mutex);
            cond_producer.wait(ul, []() { return count < size; });
            // while(count == size){
            //     cond_producer.wait(ul);
            // }
            ++count;
            std::cout << "producer produces one product, count = " << count << std::endl;
            cond_consumer.notify_all();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

auto consumer() -> void
{
    while (1) {
        {
            std::unique_lock<std::mutex> ul(g_mutex);
            cond_consumer.wait(ul, []() { return count > 0; });
            // while (count == 0) {
            //     cond_consumer.wait(ul);
            // }
            --count;
            std::cout << "consumer consumes one product, count = " << count << std::endl;
            cond_producer.notify_all();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

auto main(int argc, char* argv[]) -> int
{
    std::thread producer_thread(producer);
    std::thread consumer_thread(consumer);

    producer_thread.join();
    consumer_thread.join();

    return 0;
}