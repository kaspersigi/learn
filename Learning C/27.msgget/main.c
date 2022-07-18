#define _POSIX_C_SOURCE 200809L

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
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
// 对msgget()同样适用

// ------Message Queues--------
// key        msqid owner perms bytes nattch status
// 0x00000000 1     miku  644   128   0

// 通过msgget()第一个参数设置共享内存的key值，若使用宏定义IPC_PRIVATE，得到的key值永远为0

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

    // int msqid = msgget(IPC_PRIVATE, IPC_CREAT | 0664); //成功返回消息队列ID，失败返回-1
    int msqid = msgget(key, IPC_CREAT | 0664); //成功返回消息队列ID，失败返回-1
    if (msqid < 0) {
        printf("create message queue failure\n");
        return -1;
    }
    printf("create message queue sucess, msgid = %d\n", msqid);
    system("ipcs -q");
    msgctl(msqid, IPC_RMID, NULL);

    return 0;
}