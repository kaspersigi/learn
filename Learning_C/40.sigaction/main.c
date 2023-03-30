#define _POSIX_C_SOURCE 200809L

#include <errno.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
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

// 向线程thread发送信号sig
// 返回值 成功返回0 失败返回错误码
// int pthread_kill(pthread_t thread, int sig);

// 给信号signum设置一个处理函数，处理函数在act中指定
// act.sa_mask 信号屏蔽字 act->sa_handler 信号集处理程序
// int sigaction(int signum, const struct sigaction* act, struct sigaction* oldact);

void print(char* s)
{
    pid_t pid = getpid();
    pthread_t tid = pthread_self();
    printf("%s: %s, pid: %d, tid: %lx\n", __PRETTY_FUNCTION__, s, pid, tid);
}

// __sighandler_t
void func(int signum)
{
    printf("signum: %d\n", signum);
}

void* thread_func(void* arg)
{
    pthread_detach(pthread_self());
    // signal(SIGUSR1, func);
    struct sigaction myact;
    // sigaddset(&myact.sa_mask, SIGUSR1);
    myact.sa_handler = func;
    sigaction(SIGUSR1, &myact, NULL);

    print(arg);
    int i = 1;
    while (1) {
        pthread_testcancel();
        sleep(1);
        printf("%d\n", i++);
    }
    return (void*)0;
}

// main()就是主线程，有一些特点
// 1、main()返回时，进程结束，所有其他线程被杀死
// 2、main()参数比一般的线程多
// 3、主线程一般在默认堆栈上执行，而且可以增长到足够的长度，普通线程堆栈是受限的，一旦溢出就会产生错误
int main(int argc, char* argv[])
{
    // 非常重要！
    // 从博客上看到，主线程即进程是接受signal的对象，再由进程进行分配，由哪个线程来执行这个信号
    // 系统会找一个id最小的，没有对该信号进行屏蔽的线程，由他进行执行
    // 推测，之所以不加这句话，是因为信号交给了主线程处理，主线程没有设置信号处理函数，直接结束导致
    // signal(SIGUSR1, SIG_IGN);

    print("main thread");

    pthread_t tid_child;
    int err = pthread_create(&tid_child, NULL, thread_func, "new thread");
    if (0 != err) {
        printf("create new thread failed: %s\n", strerror(err));
        return -1;
    }

    // pthread_kill(tid_child, SIGALRM);
    // pthread_join(tid_child, NULL);
    sleep(3);
    // pthread_cancel(tid_child);
    pthread_kill(tid_child, SIGUSR1);

    sleep(3);
    pthread_kill(tid_child, SIGQUIT);
    // return 0;
    pthread_exit(0); // 主线程使用pthread_exit()退出时，进程会等待所有线程退出，才退出
}