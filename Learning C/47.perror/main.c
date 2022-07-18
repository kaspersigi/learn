#include <stdio.h>

#if 0
// perror(str)会输出"str: xxxxxxxx" xxx为库函数保存的errorno表示的字符串
void perror (const char *__s);
#endif

int main(int argc, char* argv[])
{
    FILE* fp = fopen("file.txt", "r");
    perror("main");
    // "main: No such file or directory"
    return 0;
}