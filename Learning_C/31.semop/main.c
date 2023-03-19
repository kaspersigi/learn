#define _POSIX_C_SOURCE 200809L

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>

#if 0
IPC (Inter-Process Communication，进程间通信)
一共三种IPC对象，共享内存、消息队列、信号灯

查看共享内存对象
$ ipcs -m

删除共享内存对象
$ ipcrm -m $(ID)

-m 共享内存
-q 消息队列
-s 信号灯

------Shared Memory Segments--------
key        shmid owner perms bytes nattch status
0x00000000 1     miku  644   128   0

通过shmget()第一个参数设置共享内存的key值，若使用宏定义IPC_PRIVATE，得到的key值永远为0
使用宏创建的shm只能实现有亲缘关系的进程之间通信，类似无名管道
通过ftok()创建的shm可以实现非亲缘关系的进程之间的通信，类似有名管道
对msgget()同样适用

------Message Queues--------
key        msqid owner perms bytes nattch status
0x00000000 1     miku  644   128   0

通过msgget()第一个参数设置共享内存的key值，若使用宏定义IPC_PRIVATE，得到的key值永远为0

------Semaphore Arrays--------
key        semid owner perms nsems
0x00000000 1     miku  644   0   0

信号灯和POSIX信号量的关系，信号灯是信号量的集合
#endif

#ifdef __linux__
union semun {
    int val; /* Value for SETVAL */
    struct semid_ds* buf; /* Buffer for IPC_STAT, IPC_SET */
    unsigned short* array; /* Array for GETALL, SETALL */
    struct seminfo* __buf; /* Buffer for IPC_INFO
                                           (Linux-specific) */
};
#endif

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

    // semget()比shmget() msgget()多一个参数，信号量的个数
    // int semid = semget(IPC_PRIVATE, 3, IPC_CREAT | 0664); //成功返回消息队列ID，失败返回-1
    int semid = semget(key, 3, IPC_CREAT | 0664); //成功返回消息队列ID，失败返回-1
    if (semid < 0) {
        printf("create semaphore array failure\n");
        return -1;
    }
    printf("create semaphore array sucess, semid = %d\n", semid);

    // 信号灯的第一个信号量初始化
    union semun mysemun;
    mysemun.val = 0;
    semctl(semid, 0, SETVAL, mysemun);

    // 对信号灯里的信号进行P操作
    struct sembuf mysembuf;
    mysembuf.sem_op = -1;
    // sem_op为0，等待，直到信号灯的值变为0
    // sem_op为1，释放资源，V操作
    // sem_op为-1，分配资源。P操作

    mysembuf.sem_num = 0;
    // sem_num为要操作的信号量的编号

    mysembuf.sem_flg = 0;
    // sem_flg为0，表示以阻塞方式进行通讯

    semop(semid, &mysembuf, 1);

    system("ipcs -s");
    //第二个参数为需要修改信号量，与删除无关，可以随便写
    semctl(semid, 3, IPC_RMID, NULL);

    return 0;
}