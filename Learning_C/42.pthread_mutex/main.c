#define _POSIX_C_SOURCE 200809L

#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#if 0 //用到的函数及结构体定义
typedef union {
    struct __pthread_mutex_s __data;
    char __size[__SIZEOF_PTHREAD_MUTEX_T];
    long int __align;
} pthread_mutex_t;

// 初始化互斥量
// 第一个参数 __mutex，要被初始化的互斥量共用体指针
// 第二个参数 __mutexattr，互斥量的属性，默认为NULL
int pthread_mutex_init(pthread_mutex_t* __mutex, const pthread_mutexattr_t* __mutexattr);

// 销毁一个互斥量
int pthread_mutex_destroy(pthread_mutex_t* __mutex);

// 尝试对互斥量进行加锁，如果互斥量已被锁住，不会导致该线程阻塞
// 成功返回0 失败返回错误码
int pthread_mutex_trylock(pthread_mutex_t* __mutex);

// 对互斥量进行加锁，如果互斥量已被锁住，那么会导致该线程阻塞
// 成功返回0 失败返回错误码
int pthread_mutex_lock(pthread_mutex_t* __mutex);

// 对互斥量进行解锁
// 成功返回0 失败返回错误码
int pthread_mutex_unlock(pthread_mutex_t* __mutex);
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
static pthread_mutex_t mutex;

void print(char* s)
{
    pid_t pid = getpid();
    pthread_t tid = pthread_self();
    printf("%s: %s, pid: %d, tid: %lx, count: %d\n", __PRETTY_FUNCTION__, s, pid, tid, count++);
}

void* thread_func_1(void* arg)
{
    pthread_detach(pthread_self());
    while (1) {
        pthread_testcancel();
        sleep(1);
        pthread_mutex_trylock(&mutex);
        print(arg);
        pthread_mutex_unlock(&mutex);
    }
    return (void*)0;
}

void* thread_func_2(void* arg)
{
    pthread_detach(pthread_self());
    while (1) {
        pthread_testcancel();
        sleep(1);
        pthread_mutex_trylock(&mutex);
        print(arg);
        pthread_mutex_unlock(&mutex);
    }
    return (void*)0;
}

// main()就是主线程，有一些特点
// 1、main()返回时，进程结束，所有其他线程被杀死
// 2、main()参数比一般的线程多
// 3、主线程一般在默认堆栈上执行，而且可以增长到足够的长度，普通线程堆栈是受限的，一旦溢出就会产生错误
int main(int argc, char* argv[])
{
    pthread_mutex_init(&mutex, NULL);

    print("main thread");

    pthread_t tid_child_1, tid_child_2;
    int err1 = pthread_create(&tid_child_1, NULL, thread_func_1, "new thread 1");
    if (0 != err1) {
        printf("create new thread 1 failed: %s\n", strerror(err1));
        return -1;
    }
    int err2 = pthread_create(&tid_child_2, NULL, thread_func_2, "new thread 2");
    if (0 != err2) {
        printf("create new thread 2 failed: %s\n", strerror(err2));
        return -1;
    }

    sleep(5);
    pthread_cancel(tid_child_1);
    pthread_cancel(tid_child_2);
    pthread_mutex_destroy(&mutex);
    pthread_exit(0); //主线程使用pthread_exit()退出时，进程会等待所有线程退出，才退出
}