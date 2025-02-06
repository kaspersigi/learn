#include <stdio.h>

// 在文件IO中的读写函数都是无缓存的
// 在标准IO中读写函数分为了 行缓存 无缓存 全缓存
// 行缓存 只有遇到 1、'\n' 2、写满缓存 时，才会调用系统调用函数
// 无缓存 只要用户调用这个函数，就会下将其内容写到内核中
// 全缓存 只有写满缓存才会调用系统调用函数
// 标准IO中 行缓存的读写函数有
// 1、fputs() 返回值 成功为非负 失败为-1 fgets() 返回值 成功为缓存的首地址 若已处于文件末端或失败，则返回NULL
// 2、puts() gets() 只能读写标准文件流
// 3、fprintf() printf() sprinf() fscanf() scanf() sscanf()
// fputc()有缓存 但不是行缓存
// 4、fputc() 返回值 成功为输入字符 失败为-1 fgetc() 返回值 成功为读取到字符 若已处于文件末端或失败，则返回-1

// 标准IO中 全缓存的读写函数有
// fwrite() fread() 返回值 实际读写的字节数

int main(int argc, char* argv[])
{
    FILE* fp;
    // fp = fopen("./a.txt", "w"); //如果文件不存在，则创建，读写方式打开
    fp = fopen("./a.txt", "r");
    if (fp == NULL) {
        printf("open file failure\n");
        return -1;
    }
    printf("open file success\n");

    // char write_buff[12] = "Hello Linux!";
    // int ret_write = fwrite(write_buff, 1, 12, fp);

    char read_buff[128] = {};
    int ret_read = fread(read_buff, 1, 128, fp);
    for (int i = 0; i < ret_read; ++i)
        fputc(read_buff[i], stdout);

    fclose(fp);
    return 0;
}