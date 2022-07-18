#include <dirent.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    DIR* dp = opendir("./test");
    if (dp == 0) {
        printf("open directory failure\n");
        return -1;
    }
    printf("open directory success\n");

    // struct dirent* dirent_p = readdir(dp);
    // printf("Inode number : %ld\n", dirent_p->d_ino);
    // printf("Not an offset : %ld\n", dirent_p->d_off);
    // printf("Length of this record : %d\n", dirent_p->d_reclen);
    // printf("Type of file : %d\n", dirent_p->d_type);
    // printf("Null-terminated filename : %s\n", dirent_p->d_name);

    struct dirent* p;
    // readdir() 成功则返回下个目录进入点,有错误发生或读取到目录文件尾则返回NULL,实际上就是链表
    while ((p = readdir(dp)) != NULL) {
        printf("d_name : %s\n", p->d_name);
    }

    closedir(dp);

    return 0;
}