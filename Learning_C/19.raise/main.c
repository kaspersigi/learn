#define _POSIX_C_SOURCE 200809L

#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

// raise() = kill(getpid(), sig)
// raise()只能自己给自己发送信号，成功则返回0，失败则返回-1

int main(int argc, char* argv[])
{
    printf("Hello World!");
    int ret = raise(SIGKILL); //相当于_exit()，不清空缓存
    sleep(5);

    return 0;
}