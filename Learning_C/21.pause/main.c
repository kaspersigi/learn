#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

// pause()会使进程进入sleep状态，比while(1)好

int main(int argc, char* argv[])
{
    printf("pause before\n");
    pause();
    printf("pause after\n");
    for (int i = 0; i < 20; i++) {
        sleep(1);
        printf("process things\n");
    }
    return 0;
}