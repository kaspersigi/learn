#include <coroutine>
#include <future>
#include <iostream>

using namespace std;

struct Result {
    struct promise_type {
        Result get_return_object()
        {
            std::cout << "get_return_object" << std::endl;
            return {};
        }
        std::suspend_never initial_suspend()
        {
            std::cout << "initial_suspend" << std::endl;
            return {};
        }
        std::suspend_never final_suspend() noexcept
        {
            std::cout << "final_suspend" << std::endl;
            return {};
        }
        void return_void() { std::cout << "return_void" << std::endl; }
        void unhandled_exception() { std::cout << "unhandled_exception" << std::endl; }
    };
};

struct Awaiter {
    int value;

    bool await_ready()
    {
        // 协程挂起
        return false;
    }

    void await_suspend(std::coroutine_handle<> coroutine_handle)
    {
        // 切换线程
        std::async([=]() {
            using namespace std::chrono_literals;
            // sleep 1s
            std::this_thread::sleep_for(1s);
            // 恢复协程
            coroutine_handle.resume();
        });
    }

    int await_resume()
    {
        // value 将作为 co_await 表达式的值
        return value;
    }
};

Result Coroutine()
{
    std::cout << 1 << std::endl;
    std::cout << co_await Awaiter { .value = 1000 } << std::endl; // 不知道value前“.”的含义，不过没有就会报错。
    std::cout << 2 << std::endl; // 1 秒之后再执行
};

int main(int argc, char* argv[])
{
    std::cout << "start main" << std::endl;
    Result x = Coroutine();
    std::cout << "end main" << std::endl;

    return 0;
}