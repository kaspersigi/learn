#include <stdio.h>

// 与文件IO的文件描述符fd相对应
// STDIN_FILENO = 0 标准输入
// STDOUT_FILENO = 1 标准输出
// STDERR_FILENO = 2 标准输出错误

// 标准IO的标准文件流指针
//  stdin 标准输入流 行缓存
//  stdout 标准输出流 行缓存
//  stderr 标准输出错误流 无缓存

// fopen mode
// "r" 只读
// "a" "w" 如果文件不存在，则创建之，同时"a"追加写，"w"清空写
// "+" 读写方式打开
// "b" 二进制形式打开

// 默认创建文件权限为 0666 & (~umask)
// 一般umask为0002，因此创建文件默认权限为0664

int main(int argc, char* argv[])
{
    FILE* fp;
    fp = fopen("./a.txt", "w+"); // 如果文件不存在，则创建，读写方式打开
    if (fp == NULL) {
        printf("create file failure\n");
        return -1;
    }
    printf("create file success\n");
    fclose(fp);

    return 0;
}