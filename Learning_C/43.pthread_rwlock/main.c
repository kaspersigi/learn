#define _POSIX_C_SOURCE 200809L

#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// 读写锁与互斥量类似，不过读写锁有更高的并行性。
// 互斥量要么加锁，要么并不加锁，同时只有一个线程能够访问
// 读写锁，可以让多个线程同时读取

#if 0 // 用到的函数及结构体定义
typedef union {
    struct __pthread_rwlock_arch_t __data;
    char __size[__SIZEOF_PTHREAD_RWLOCK_T];
    long int __align;
} pthread_rwlock_t;

// 初始化读写锁
int pthread_rwlock_init(pthread_rwlock_t* __restrict__ __rwlock, const pthread_rwlockattr_t* __restrict__ __attr);

// 销毁读写锁
int pthread_rwlock_destroy(pthread_rwlock_t* __rwlock);

// 读加锁
int pthread_rwlock_tryrdlock(pthread_rwlock_t* __rwlock);
int pthread_rwlock_rdlock(pthread_rwlock_t* __rwlock);

// 写加锁
int pthread_rwlock_trywrlock(pthread_rwlock_t* __rwlock);
int pthread_rwlock_wrlock(pthread_rwlock_t* __rwlock);

// 解锁
int pthread_rwlock_unlock(pthread_rwlock_t *__rwlock);

#endif

// 第一个参数 新线程ID
// 第二个参数 线程属性（调度策略、继承性、分离性...）NULL为默认属性
// 第三个参数 新线程启动函数
// 第四个参数 传递给新线程的参数
// 返回值 成功 返回0 失败 返回错误码
// int pthread_create(pthread_t* thread, const pthread_attr_t* attr, void* (*start_routine)(void*), void* arg);

// 线程的分离属性：
// 1、分离一个正在运行的程序并不影响他，仅仅是通知该系统，该线程结束时，其所属资源可以回收。一个没有被分离的线程在中止时，会保留他的虚拟内存，包括他们的堆栈和其他系统资源，有时这种线程被称为“僵尸线程”，创建线程时，默认是非分离的
// 2、如果线程具备分离属性，线程中止时会被立即回收，回收将释放掉所有线程中止时，未释放掉的系统资源和进程资源，包括保存线程返回值的内存空间、堆栈、保存寄存器的内存文件等
// 3、终止被分离的线程，会释放掉所有的系统资源，但是你必须释放由该线程占有的程序资源，由malloc或者mmap分配的内存，可以在任何时候由任何线程释放，条件变量、互斥量、信号灯可以由任何线程销毁，只要他们被解锁了或者没有线程等待。但是只有互斥量的主人才能解锁它，所以在线程中止前，你需要解锁互斥量

static int count = 1;
static pthread_rwlock_t rwlock;

void print(char* s)
{
    pid_t pid = getpid();
    pthread_t tid = pthread_self();
    printf("%s: %s, pid: %d, tid: %lx, count: %d\n", __PRETTY_FUNCTION__, s, pid, tid, count);
}

void* thread_func_read_1(void* arg)
{
    pthread_detach(pthread_self());
    while (1) {
        pthread_testcancel();
        sleep(1);
        pthread_rwlock_tryrdlock(&rwlock);
        print(arg);
        pthread_rwlock_unlock(&rwlock);
    }
    return (void*)0;
}

void* thread_func_read_2(void* arg)
{
    pthread_detach(pthread_self());
    while (1) {
        pthread_testcancel();
        sleep(2);
        pthread_rwlock_tryrdlock(&rwlock);
        print(arg);
        pthread_rwlock_unlock(&rwlock);
    }
    return (void*)0;
}

void* thread_func_write(void* arg)
{
    pthread_detach(pthread_self());
    while (1) {
        pthread_testcancel();
        sleep(3);
        pthread_rwlock_trywrlock(&rwlock);
        print(arg);
        count++;
        pthread_rwlock_unlock(&rwlock);
    }
    return (void*)0;
}

// main()就是主线程，有一些特点
// 1、main()返回时，进程结束，所有其他线程被杀死
// 2、main()参数比一般的线程多
// 3、主线程一般在默认堆栈上执行，而且可以增长到足够的长度，普通线程堆栈是受限的，一旦溢出就会产生错误
int main(int argc, char* argv[])
{
    print("main thread");
    pthread_rwlock_init(&rwlock, NULL);

    pthread_t tid_child_1,
        tid_child_2, tid_child_3;
    int err1 = pthread_create(&tid_child_1, NULL, thread_func_read_1, "thread read 1");
    if (0 != err1) {
        printf("create new thread 1 failed: %s\n", strerror(err1));
        return -1;
    }
    int err2 = pthread_create(&tid_child_2, NULL, thread_func_read_2, "thread read 2");
    if (0 != err2) {
        printf("create new thread 2 failed: %s\n", strerror(err2));
        return -1;
    }
    int err3 = pthread_create(&tid_child_3, NULL, thread_func_write, "thread write");
    if (0 != err3) {
        printf("create new thread 3 failed: %s\n", strerror(err3));
        return -1;
    }

    sleep(9);
    pthread_cancel(tid_child_1);
    pthread_cancel(tid_child_2);
    pthread_cancel(tid_child_3);
    pthread_rwlock_destroy(&rwlock);
    pthread_exit(0); // 主线程使用pthread_exit()退出时，进程会等待所有线程退出，才退出
}