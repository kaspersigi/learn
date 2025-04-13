#include "ftrace.h"
#include <chrono>
#include <functional>
#include <print>
#include <thread>

#if 0
什么是异步和同步，阻塞和非阻塞？

同步 (Synchronous) vs 异步 (Asynchronous)

同步 (Synchronous)
定义：操作按顺序执行，必须等待当前操作完成才能进行下一个操作
特点：
代码执行顺序与编写顺序一致
调用者必须等待被调用操作完成才能继续
直观、易于理解和调试

异步 (Asynchronous)
定义：操作可以并发执行，不必等待当前操作完成
特点：
调用后立即返回，不等待操作完成
通过回调、事件或future/promise等方式获取结果
提高系统吞吐量和资源利用率
代码结构更复杂

阻塞 (Blocking) vs 非阻塞 (Non-blocking)

阻塞 (Blocking)
定义：调用操作后，线程会被挂起，直到操作完成
特点：
线程无法执行其他工作
简单直接，但资源利用率低
可能导致程序"卡住"

非阻塞 (Non-blocking)
定义：调用操作后立即返回，无论操作是否完成
特点：
线程可以继续做其他工作
需要轮询或事件通知机制检查操作状态
资源利用率高，但编程复杂度高

组合概念
这四个概念可以两两组合：

同步阻塞：最常见的模式，简单但效率低
示例：普通函数调用、阻塞I/O

同步非阻塞：轮询模式，效率不高
示例：轮询检查文件是否可读

异步阻塞：较少见，通常不是有意设计
示例：使用select/poll等待多个异步操作

异步非阻塞：高性能模式，但编程复杂
示例：Node.js的I/O模型、现代异步框架

实际应用中的选择
Web服务器：通常使用异步非阻塞模型（如Nginx、Node.js）
桌面应用：通常使用同步阻塞模型，配合多线程
高性能计算：根据任务特性选择同步或异步
#endif

class Child {
public:
    Child() = default;
    ~Child() = default;

protected:
    Child(const Child& obj) = delete;
    Child(Child&& obj) = delete;
    Child& operator=(const Child& obj) = delete;
    Child& operator=(Child&& obj) = delete;

public:
    void doing(int sleep, int& value);
};

auto Child::doing(int sleep, int& value) -> void
{
    Ftrace::ftrace_duration_begin("ChildThread");
    std::println("{}: process E", __PRETTY_FUNCTION__);
    std::this_thread::sleep_for(std::chrono::seconds(sleep));
    value = sleep;
    std::println("{}: process X", __PRETTY_FUNCTION__);
    Ftrace::ftrace_duration_end();
}

auto main(int argc, char* argv[]) -> int
{
    Ftrace::ftrace_duration_begin("MainThread");
    std::println("{}: process E", __PRETTY_FUNCTION__);
    Child child;
    int value = 0;
    std::thread t(&Child::doing, &child, 4, std::ref(value));
    {
        // Async part
        std::println("value = {}", value);
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
    t.join();
    std::println("value = {}", value);
    std::println("{}: process X", __PRETTY_FUNCTION__);
    Ftrace::ftrace_duration_end();

    return 0;
}