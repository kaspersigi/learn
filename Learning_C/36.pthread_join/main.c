#define _POSIX_C_SOURCE 200809L

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

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

// 调用该函数的线程会一直阻塞，直到指定的线程thread调用pthread_exit、从启动例程返回或者被取消
// 第一个参数 thread就是指定的线程ID
// 第二个参数 retval是指定线程的返回码，如果线程被取消，那么retval被置为PTHREAD_CANCELED
// 返回值 成功返回0 失败返回错误码
// int pthread_join(pthread_t thread, void** retval);

// 调用pthread_join()会使指定的线程处于分离状态，如果指定线程已经处于分离状态，那么调用就会失败

// pthread_detach()可以分离一个线程，线程可以分离自己
// 返回值 成功返回0 失败返回错误码
// int pthread_detach(pthread_t thread);

void print(char* s)
{
    pid_t pid = getpid();
    pthread_t tid = pthread_self();
    printf("%s: %s, pid: %d, tid: %lx\n", __PRETTY_FUNCTION__, s, pid, tid);
}

void* thread_func(void* arg)
{
    print(arg);
    sleep(2);
    return (void*)0;
}

// main()就是主线程，有一些特点
// 1、main()返回时，进程结束，所有其他线程被杀死
// 2、main()参数比一般的线程多
// 3、主线程一般在默认堆栈上执行，而且可以增长到足够的长度，普通线程堆栈是受限的，一旦溢出就会产生错误
int main(int argc, char* argv[])
{
    print("main thread");

    pthread_t tid_child;
    int err = pthread_create(&tid_child, NULL, thread_func, "new thread");
    if (0 != err) {
        printf("create new thread failed: %s\n", strerror(err));
        return -1;
    }

    pthread_join(tid_child, NULL);
    return 0;
}