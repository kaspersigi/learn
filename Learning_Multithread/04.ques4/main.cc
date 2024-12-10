#include <iostream>

#if 0
有一个写者很多读者，多个读者可以同时读文件，但写者在写文件时不允许有读者在读文件，同样有读者读时写者也不能写
#endif

auto main(int argc, char* argv[]) -> int
{
    std::cout << "Hello World!" << std::endl;
    return 0;
}