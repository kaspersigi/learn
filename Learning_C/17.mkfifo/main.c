#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

const char* FIFO = "./myfifo";

int main(int argc, char* argv[])
{
    int ret;
    // mode % (~umask)
    ret = mkfifo(FIFO, 0664);
    if (ret < 0) {
        printf("create myfifo failure\n");
        return -1;
    }
    printf("create myfifo success\n");

#if 0
    int fd[2] = {};

    fd[0] = open(FIFO, O_RDONLY);
    fd[1] = open(FIFO, O_WRONLY);
    close(fd[0]);
    close(fd[1]);
#endif

    unlink(FIFO);

    return 0;
}