#include <dirent.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    DIR* dp = opendir("./test"); //不能创建目录
    if (dp == 0) {
        printf("open directory failure\n");
        return -1;
    }
    printf("open directory success\n");

    closedir(dp);

    return 0;
}