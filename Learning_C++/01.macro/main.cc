#include <iostream>

auto main(int argc, char* argv[]) -> int
{
    std::cout << "linux: " << __linux__ << std::endl; // 是否linux系统
    std::cout << "cplusplus: " << __cplusplus << std::endl; // 编译时c++标准
    std::cout << "version: " << __VERSION__ << std::endl; // 编译时编译器版本
    std::cout << "file: " << __FILE__ << std::endl; // 文件名
    std::cout << "base file: " << __BASE_FILE__ << std::endl; // 未被include时文件名，一般用于头文件中
    std::cout << "date: " << __DATE__ << std::endl; // 编译日期
    std::cout << "time: " << __TIME__ << std::endl; // 编译时间
    std::cout << "timestamp: " << __TIMESTAMP__ << std::endl; // 文件修改日期
    std::cout << "func: " << __func__ << std::endl; // 函数名，c99起支持，现在比__FUNCTION__更受支持
    std::cout << "function: " << __FUNCTION__ << std::endl; // 函数名
    std::cout << "pretty funcion: " << __PRETTY_FUNCTION__ << std::endl; // 函数签名
    std::cout << "line: " << __LINE__ << std::endl; // 行数

    return 0;
}