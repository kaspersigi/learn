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

int main(int argc, char* argv[])
{
#if 1
    FILE* fp;
    char read_buffer[128] = {};
    char write_buffer[128] = {};
    fp = fopen("./a.txt", "r"); //如果文件不存在，则创建，读写方式打开
    if (fp == NULL) {
        printf("creat file failure\n");
        return -1;
    }
    printf("creat file success\n");

    // fputs("Hello Linux!", fp);
    // fputs("Hello Linux!", stdout);

    char* p = fgets(read_buffer, 128, fp);

    printf("%s\n", read_buffer);

    // fflush(fp); //fflush() 会强制刷新缓存，将库函数内容，写入内核

    fclose(fp); // fclose() 会强制写缓存
#endif

#if 0
    // 1、gets()不会将'\n'写入缓存，fgets()会
    // 2、puts()会在输出时增加一个'\n',fputs()不会

    char read_buffer[128] = {};
    char write_buffer[128] = {};
    int ret_read = gets(read_buffer);
    int ret_write = puts(read_buffer);
#endif

#if 0
    // 1、fprintf() 输出到文件流中去
    // 2、printf() 只能输出到标准输出流中去（显示器）
    // 3、sprintf() 输出到字符串中去

    fprintf(stdout, "Hello Linux!");
#endif

#if 0
    char cin = fgetc(stdin);
    char cout = fputc(cin, stdout);
#endif

    return 0;
}