#define _POSIX_C_SOURCE 200809L

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

// IPC (Inter-Process Communication，进程间通信)
// 一共三种IPC对象，共享内存、消息队列、信号灯

// 查看共享内存对象
// $ ipcs -m

// 删除共享内存对象
// $ ipcrm -m $(ID)

// -m 共享内存
// -q 消息队列
// -s 信号灯

// ------Shared Memory Segments--------
// key        shmid owner perms bytes nattch status
// 0x00000000 1     miku  644   128   0

// 通过shmget()第一个参数设置共享内存的key值，若使用宏定义IPC_PRIVATE，得到的key值永远为0
// 使用宏创建的shm只能实现有亲缘关系的进程之间通信，类似无名管道
// 通过ftok()创建的shm可以实现非亲缘关系的进程之间的通信，类似有名管道

int main(int argc, char* argv[])
{
    int fd = open("./a.txt", O_CREAT | O_EXCL | O_RDONLY, 0664);
    if (fd < 0) {
        printf("open file failure, fd = %d\n", fd);
    } else {
        printf("open file sucess, fd = %d\n", fd);
        close(fd);
    }

    // int proj_id 必须非0，一般只用到8bit，所以填一个char字符，比较方便
    int key = ftok("./a.txt", 'a'); // fork()不会自行创建文件，如果文件本身不存在，会失败
    if (key < 0) {
        printf("create key failure\n");
        return -2;
    }
    printf("create key success, key = %X\n", key);

    int shmid = shmget(key, 128, IPC_CREAT | 0664);
    if (shmid < 0) {
        printf("create share memory failure\n");
        return -1;
    }
    printf("create share memory sucess, shmid = %d\n", shmid);
    system("ipcs -m");

    // NULL 系统自己选择用户空间地址，和内核空间进行映射
    // 0 映射的内存mode为可读写
    // shmat()成功则返回映射后的地址，失败则返回NULL
    char* shm_p = (char*)shmat(shmid, NULL, 0);
    if (shm_p == NULL) {
        printf("shmat function failure\n");
        return -3;
    }

    // write share memory
    fgets(shm_p, 128, stdin);

    // start read share memory
    printf("share memory data: %s\n", shm_p);
    printf("share memory data read twice: %s\n", shm_p);
    // 共享内存和管道，还是有一定的区别
    // 1、共享内存读取后，内容依旧存在于共享内存中，不会被删除
    // 2、共享内存创建后，一直存在于内核中，程序退出也不会消失，除非被删除或者系统关闭

    shmdt(shm_p); // shmdt()只是删除了地址映射，没有删除内核中的共享内存
    // 成功返回0 失败返回-1

    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}