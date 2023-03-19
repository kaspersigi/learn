#define _POSIX_C_SOURCE 200809L

#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

// __sighandler_t
void func(int signum)
{
    printf("%d\n", signum);
}

int main(int argc, char* argv[])
{
    // signal(SIGPIPE, SIG_IGN); //忽略SIGPIPE信号
    signal(SIGUSR1, func);
    sleep(5);
    raise(SIGUSR1);
    printf("Hello World!");
    return 0;
}