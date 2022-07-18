#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    int fd[2] = {};
    int ret;
    ret = pipe(fd);
    if (ret < 0) {
        printf("create pip failure\n");
        return -1;
    }
    printf("create pip success fd[0] = %d, fd[1] = %d\n", fd[0], fd[1]);
    // fd[0] read fd[1] write 都是单向队列

    //管道的三个特征
    // 1、读完就删
    // 2、读阻塞（读完后无内容可读，即阻塞
    // 3、写阻塞（写满后无法继续写入，即阻塞

    char write_buf[] = "Hello Linux!";
    char read_buf[128] = {};
    int ret_write = write(fd[1], write_buf, sizeof(write_buf));
    read(fd[0], read_buf, ret_write);
    fputs(read_buf, stdout);

    close(fd[0]);
    close(fd[1]);

    return 0;
}