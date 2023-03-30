#define _POSIX_C_SOURCE 200809L

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

typedef struct msgbuff {
    long type; // 第一个参数必须是类型
    char voltage[124]; // 自定义类型，传输的消息内容，这里是电压的值
    char ID[4]; // 自定义内容，这里是某设备ID
} msgbuff;

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
    int msqid = msgget(key, IPC_CREAT | 0664); // 成功返回消息队列ID，失败返回-1
    if (msqid < 0) {
        printf("create message queue failure\n");
        return -1;
    }
    printf("create message queue sucess, msgid = %d\n", msqid);

    // init sendbuff
    msgbuff sendbuff; // 实例化msgbuff对象
    sendbuff.type = 100;
    printf("please input message: \n");
    fgets(sendbuff.voltage, 124, stdin);

    // start write message to message queue
    // 第二个参数为定义的结构体
    // 第三个参数为真正传输消息的大小
    // flag 0 表示，没有消息，会一直阻塞
    // 返回值 成功返回0 失败返回-1
    msgsnd(msqid, (void*)&sendbuff, strlen(sendbuff.voltage), 0);

    system("ipcs -q");
    msgctl(msqid, IPC_RMID, NULL);

    return 0;
}