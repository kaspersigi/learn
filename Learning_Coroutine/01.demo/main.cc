#include <coroutine>
#include <future>
#include <iostream>

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
        return false;
    }

    void await_suspend(std::coroutine_handle<> coroutine_handle)
    {
        std::async([=]() {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            coroutine_handle.resume();
        });
    }

    int await_resume()
    {
        return value;
    }
};

Result Coroutine()
{
    std::cout << 1 << std::endl;
    std::cout << co_await Awaiter { 1000 } << std::endl;
    std::cout << 2 << std::endl;
};

int main(int argc, char* argv[])
{
    std::cout << "start main" << std::endl;
    Result c = Coroutine();
    std::cout << "end main" << std::endl;

    return 0;
}