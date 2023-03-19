#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

// fork()执行一次，返回两个值
//对于父进程，fork()返回子进程的进程号
//对于子进程，fork()返回0
//主进程退出时，子进程并不会自动退出

int main(int argc, char* argv[])
{
    int a = 5;
    int b = 2;
    pid_t pid;
    pid = fork();

    if (pid == 0) {
        a = a - 4;
        printf("I'm a child process with PID [%d], the value of a: %d, the value of b: %d.\n", pid, a, b);
        exit(0);
    } else if (pid < 0)
        perror("fork");
    else {
        printf("I'm a parent process, with a PID [%d], the value of a: %d, the value of b: %d.\n", pid, a, b);
    }
    return 0;
}