#include <stdio.h>

int main(int argc, char* argv[])
{
    // printf("stdc: %d\n", __linux__); // 是否linux系统
    printf("stdc: %d\n", __STDC__); // 是否ANIC C
    printf("stdc version: %ld\n", __STDC_VERSION__); // 编译时C标准
    printf("version: %s\n", __VERSION__); // 编译器版本
    printf("file: %s\n", __FILE__); // 文件名
    printf("base file: %s\n", __BASE_FILE__); // 未被include时文件名，一般用于头文件中
    printf("date: %s\n", __DATE__); // 编译日期
    printf("time: %s\n", __TIME__); // 编译时间
    printf("timestamp: %s\n", __TIMESTAMP__); // 文件修改日期
    printf("func: %s\n", __func__); // 函数名，c99起支持，现在比__FUNCTION__更受支持
    printf("function: %s\n", __FUNCTION__); // 函数名
    printf("pretty function: %s\n", __PRETTY_FUNCTION__); // 函数签名
    printf("line: %d\n", __LINE__); // 行数
    return 0;
}