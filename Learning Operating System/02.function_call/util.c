#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    int fd = open(argv[1], O_RDWR);
    char buffer[1024] = { 0 };
    if (fd) {
        int ret = read(fd, buffer, 1000);
        printf("%d\n", ret);
        if (ret > 0 && ret <= 510) {
            buffer[510] = 0x55;
            buffer[511] = 0xAA;
        }
        lseek(fd, 0, 0);
        ret = write(fd, buffer, 512);
        close(fd);
    }
    return 0;
}