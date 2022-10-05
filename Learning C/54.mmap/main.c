#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    int fd;
    struct stat st;

    if ((fd = open("./main", O_RDONLY)) < 0) {
        perror("open");
        exit(-1);
    }
    if ((fstat(fd, &st)) < 0) {
        perror("fstat");
        exit(-1);
    }
    printf("%ld\n", st.st_size);

    void* addr = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (MAP_FAILED == addr) {
        perror("mmap");
        exit(-1);
    }
    printf("%p\n", addr);
    printf("%c\n", *((char*)addr + 1));
    printf("%c\n", *((char*)addr + 2));
    printf("%c\n", *((char*)addr + 3));
    munmap(addr, st.st_size);
    close(fd);

    return 0;
}