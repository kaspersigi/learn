#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char* argv[])
{
    int ret = mkdir("./test", 0775);
    if (ret < 0) {
        printf("create directory failure\n");
        return -1;
    }
    printf("create directory success\n");

    return 0;
}