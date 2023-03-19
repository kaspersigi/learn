#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    int fd;
    char read_buf[128] = {};
    int write_ret, read_ret;
    fd = open("./a.txt", O_RDONLY);
    // open()返回值为文件inode号，即文件标识符
    if (fd < 0) {
        printf("open file a.txt failure\n");
        return -1;
    }
    printf("open a.txt success, fd = %d\n", fd);

    // start read
    read_ret = read(fd, read_buf, 128);

    printf("read_ret = %d\n", read_ret);
    printf("%s\n", read_buf);
    close(fd);

    return 0;
}