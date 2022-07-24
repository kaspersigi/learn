#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

// open() flag参数
// O_RDONLY 以只读方式打开
// O_WRONLY 以只写方式打开
// O_RDWR 以读写方式打开
// O_CREAT 若文件不存在则创建之
// O_EXCL 结合O_CTREAT参数使用，专门用于创建文件，如果文件已存在，则不会打开
// O_TRUNC 截断已有文件，使其长度为零
// O_APPEND 总在文件尾部追加数据
// O_ASYNC 当I/O操作可行时，产生信号(signal)通知进程
// O_NONBLOCK 以非阻塞方式打开
// O_SYNC 以同步方式写入文件
// O_NOCTTY 如果正在打开的文件属于终端设备，O_NOCTTY标志防止其成为控制终端

// open() 创建文件权限
// mode & ~(umask)
// 在docker中运行$ umask 值为 0002

// 文件描述符fd
// STDIN_FILENO = 0 标准输入
// STDOUT_FILENO = 1 标准输出
// STDERR_FILENO = 2 标准输出错误

int main(int argc, char* argv[])
{
    int fd;

    int umask = 0002;
    int mode = 0664;
    int out = mode & (~umask);
    printf("%d\n", out);

    // fd = open("./a.txt", O_APPEND | O_RDWR);
    // fd = open("./a.txt", O_TRUNC | O_RDWR);
    fd = open("./a.txt", O_CREAT | O_RDWR | O_EXCL, 0664);
    if (fd < 0) {
        printf("create file a.txt failure\n");
        return -1;
    }
    printf("create a.txt success, fd = %d\n", fd);
    close(fd);
    return 0;
}