#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

// IPC (Inter-Process Communication，进程间通信)
// 一共三种IPC对象，共享内存、消息队列、信号量

// 查看共享内存对象
// $ ipcs -m

// 删除共享内存对象
// $ ipcrm -m $(ID)

// -m 共享内存
// -q 消息队列
// -s 信号量

// ------Shared Memory Segments--------
// key        shmid owner perms bytes nattch status
// 0x00000000 1     miku  644   128   0

// 通过shmget()第一个参数设置共享内存的key值，若使用宏定义IPC_PRIVATE，得到的key值永远为0
// 使用宏创建的shm只能实现有亲缘关系的进程之间通信，类似无名管道
// 通过ftok()创建的shm可以实现非亲缘关系的进程之间的通信，类似有名管道

int main(int argc, char* argv[])
{
    int shmid = shmget(IPC_PRIVATE, 128, 0644);
    if (shmid < 0) {
        printf("create share memory failure\n");
        return -1;
    }
    printf("create share memory sucess, shmid = %d\n", shmid);
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}