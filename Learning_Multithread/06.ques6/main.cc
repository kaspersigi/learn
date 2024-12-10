#include <iostream>

#if 0
1）有一int型全局变量g_Flag初始值为0
2） 在主线称中起动线程1，打印“this is thread1”，并将g_Flag设置为1
3） 在主线称中启动线程2，打印“this is thread2”，并将g_Flag设置为2
4） 线程序1需要在线程2退出后才能退出
5） 主线程在检测到g_Flag从1变为2，或者从2变为1的时候退出
#endif

auto main(int argc, char* argv[]) -> int
{
    std::cout << "Hello World!" << std::endl;
    return 0;
}