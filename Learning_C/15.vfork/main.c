#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

// vfork()系统调用不同于fork，用vfork创建的子进程与父进程共享地址空间，
// 如果子进程修改了某个变量，将影响到父进程
// vfork()创建的子进程必须显式调用exit()来结束
// 父进程等待子进程执行完毕后，才继续进行
// 否则子进程将不能结束，而fork()不存在这个情况

// 另 vfork()在macOS和Linux上行为不一样
// Linux的glibc2.12之前和glibc2.12之后也不一样

int main(int argc, char* argv[])
{
    if (vfork() == 0) {
        printf("This is the child process\n");
        exit(0);
    } else
        printf("This is the parent process\n");
    return 0;
}