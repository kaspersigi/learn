#define _POSIX_C_SOURCE 200809L

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// 条件变量需要互斥量配合使用
// 条件变量的优势
// 普通的互斥锁和读写锁，一次只能锁住一个线程，一次只能打开一个线程
// 条件变量可以一次锁住一组线程，一次打开一组线程
// 因此在线程同步中，在多生产者-多消费者模型中，非常实用

#if 0 // 用到的函数及结构体定义
// 用于阻塞和唤醒多个线程，因此存储了多个线程的ID
typedef union {
    struct __pthread_cond_s __data;
    char __size[__SIZEOF_PTHREAD_COND_T];
    __extension__ long long int __align;
} pthread_cond_t;

struct timespec {
    __time_t tv_sec; /* Seconds.  */
#if __WORDSIZE == 64                                            \
    || (defined __SYSCALL_WORDSIZE && __SYSCALL_WORDSIZE == 64) \
    || __TIMESIZE == 32
    __syscall_slong_t tv_nsec; /* Nanoseconds.  */
#else
#if __BYTE_ORDER == __BIG_ENDIAN
    int : 32; /* Padding.  */
    long int tv_nsec; /* Nanoseconds.  */
#else
    long int tv_nsec; /* Nanoseconds.  */
    int : 32; /* Padding.  */
#endif
#endif
};

int pthread_cond_init(pthread_cond_t* __restrict__ __cond, const pthread_condattr_t* __restrict__ __cond_attr);

int pthread_cond_destroy(pthread_cond_t* __cond);

int pthread_cond_wait(pthread_cond_t* __restrict__ __cond, pthread_mutex_t* __restrict__ __mutex);

int pthread_cond_timedwait(pthread_cond_t* __restrict__ __cond, pthread_mutex_t* __restrict__ __mutex, const struct timespec* __restrict__ __abstime);

int pthread_cond_signal(pthread_cond_t* __cond);

int pthread_cond_broadcast(pthread_cond_t* __cond);

#endif

static pthread_cond_t cond;
static pthread_mutex_t mutex;

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

// 任务链表
typedef struct Node {
    int number;
    struct Node* next;
} Node;

// 任务链表头节点
static Node* head;

void print(char* s)
{
    pid_t pid = getpid();
    pthread_t tid = pthread_self();
    printf("%s: %s, pid: %d, tid: %lx\n", __PRETTY_FUNCTION__, s, pid, tid);
}

void* producer_f(void* arg)
{
    print((char*)arg);
    while (1) {
        pthread_mutex_lock(&mutex);

        Node* new_node = (Node*)malloc(sizeof(Node));
        new_node->number = rand() % 1000;
        new_node->next = head;
        head = new_node;
        printf("%s: %s, pid: %d, tid: %lx, number: %d\n", __PRETTY_FUNCTION__, (char*)arg, getpid(), pthread_self(), new_node->number);

        pthread_mutex_unlock(&mutex);
        // 唤醒消费者线程
        pthread_cond_broadcast(&cond);
        sleep(rand() % 3);
    }
    return NULL;
}

void* consumer_f(void* arg)
{
    print((char*)arg);

    // 阻塞消费者线程
    while (1) {

        pthread_mutex_lock(&mutex);
        while (head == NULL) {
            pthread_cond_wait(&cond, &mutex);
        }

        Node* node = head;
        printf("%s: %s, pid: %d, tid: %lx, number: %d\n", __PRETTY_FUNCTION__, (char*)arg, getpid(), pthread_self(), node->number);
        head = head->next;
        free(node);

        pthread_mutex_unlock(&mutex);
        sleep(rand() % 3);
    }
    return NULL;
}

// main()就是主线程，有一些特点
// 1、main()返回时，进程结束，所有其他线程被杀死
// 2、main()参数比一般的线程多
// 3、主线程一般在默认堆栈上执行，而且可以增长到足够的长度，普通线程堆栈是受限的，一旦溢出就会产生错误
int main(int argc, char* argv[])
{
    print("main thread");
    pthread_cond_init(&cond, NULL);
    pthread_mutex_init(&mutex, NULL);

    pthread_t producer_a[5], consumer_a[5];
    for (int i = 0; i < 5; ++i)
        pthread_create(&producer_a[i], NULL, producer_f, "producer thread");
    for (int i = 0; i < 5; ++i)
        pthread_create(&consumer_a[i], NULL, consumer_f, "consumer thread");

    for (int i = 0; i < 5; ++i) {
        pthread_join(producer_a[i], NULL);
        pthread_join(consumer_a[i], NULL);
    }

    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&mutex);
    pthread_exit(0); // 主线程使用pthread_exit()退出时，进程会等待所有线程退出，才退出
}