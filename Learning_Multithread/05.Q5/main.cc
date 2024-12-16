#include <iostream>

#if 0
线程安全的 queue
STL 中的 queue 是非线程安全的，一个组合操作：front();  pop() 先读取队首元素然后删除队首元素，若是有多个线程执行这个组合操作的话，可能会发生执行序列交替执行，导致一些意想不到的行为。因此需要重新设计线程安全的 queue 的接口
#endif

auto main(int argc, char* argv[]) -> int
{
    std::cout << "Hello World!" << std::endl;
    return 0;
}