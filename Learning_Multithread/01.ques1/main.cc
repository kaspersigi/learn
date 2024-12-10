#include <iostream>

#if 0
子线程循环 10 次，接着主线程循环 100 次，接着又回到子线程循环 10 次，接着再回到主线程又循环 100 次，如此循环50次，试写出代码
#endif

auto main(int argc, char* argv[]) -> int
{
    std::cout << "Hello World!" << std::endl;
    return 0;
}