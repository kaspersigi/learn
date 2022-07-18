#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    int fd;
    // char buf[] = "Hello Linux!"; 大小为13，末尾还有\0 写入文件会引起编码问题
    char buf[12] = "Hello Linux!";
    int write_ret;
    fd = open("./a.txt", O_TRUNC | O_RDWR | O_CREAT, 0664);
    // open()返回值为文件inode号(非负整数)，即文件标识符
    //失败返回-1
    if (fd < 0) {
        printf("open file a.txt failure\n");
        return -1;
    }
    printf("open a.txt success, fd = %d\n", fd);
    write_ret = write(fd, buf, sizeof(buf));
    // write()返回值为实际写入内核的字节数
    printf("write_ret = %d\n", write_ret);
    close(fd);

    return 0;
}