#define _POSIX_C_SOURCE 200809L

#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

// alarm()只能自己给自己发送信号

int main(int argc, char* argv[])
{
    printf("alarm before\n");
    alarm(9); //若干秒后，发送一个SIGALRM信号
    printf("alarm after\n");
    for (int i = 0; i < 20; i++) {
        sleep(1);
        printf("process things\n");
    }
    return 0;
}