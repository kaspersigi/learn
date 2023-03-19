#define _POSIX_C_SOURCE 200809L

#include <errno.h>
#include <math.h>
#include <pthread.h>
#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

typedef void (*my_fun)(int);
#define fun3 ((my_fun)1)

// signal通信框架
// 1、信号的发送 kill() raise() alarm()
// 2、信号的接收 pause() sleep() while(1)
// 3、信号的处理 signal()

// sigaction()是signal()的高级版，可以完全取代signal()
// SIG信号预定义行为
// 1、SIGHUP
// 2、SIGINT 用户键入终端中断字符(ctrl+c)时，发送给终端前台进程 默认终止进程
// 3、SIGQUIT 用户键入退出字符(ctrl+\)时，发送给终端前台进程 默认终止进程
// 4、SIGILL 进程试图执行非法的（格式不正确的）机器指令
// 5、SIGTRAP
// 6、SIGABRT 系统调用函数abort()产生 默认终止进程
// 7、SIGBUS 发生某种内存访问错误
// 8、SIGFPE 产生算数错误，例如除0错误
// 9、SIGKILL 立即结束进程，不能被阻塞，忽略和捕获
// 10、SIGUSR1
// 11、SIGSEGV 段错误，程序对内存的引用无效时产生
// 12、SIGUSR2
// 13、SIGPIPE 当某一进程试图向管道、FIFO、套接字写入数据时，如果读文件描述符已被关闭，产生该信号
// 14、SIGALRM alarm()或setitimer()定时器到期而产生 默认终止进程
// 15、SIGTERM 用来终止进程的标准信号
// 16、SIGSTKFLT
// 17、SIGPCHLD 子进程状态改变时，父进程收到 默认忽略
// 18、SIGCONT 发送给停止的进程 默认恢复运行
// 19、SIGSTOP 暂停一个进程，不能被阻塞，忽略和捕获
// 20、SIGTSTP 终端暂停信号，用户键入终端中断字符(ctrl+z)时，发送给终端前台进程 默认暂停进程
// 21、SIGTTIN
// 22、SIGTTOU
// 23、SIGURG
// 24、SIGXCPU
// 25、SIGXFSZ
// 26、SIGVTALRM
// 27、SIGPROF
// 28、SIGWINCH
// 29、SIGIO
// 30、SIGPWR 电源故障信号
// 31、SIGSYS 系统调用有误

void fun1(int num)
{
    printf("%s: num = %d\n", __PRETTY_FUNCTION__, num);
}

my_fun fun2(int num, my_fun fun)
{
    printf("%s: num = %d\n", __PRETTY_FUNCTION__, num);
    printf("%s: fun = %p\n", __PRETTY_FUNCTION__, fun);
    if ((ptrdiff_t)fun == -1) {
        printf("This is SIG_ERR\n");
    } else if ((ptrdiff_t)fun == 0) {
        printf("This is SIG_DFL\n");
    } else if ((ptrdiff_t)fun == 1) {
        printf("This is SIG_IGN\n");
    }
    return fun;
}

//编译器原因，gcc对没有变量的东西sizeof，返回不是0，而是1

int main(int argc, char* argv[])
{
    int* p;

#if (__WORDSIZE == 32)
    // printf("%d\n", sizeof(long));
    printf("%d\n", sizeof(ptrdiff_t));
    printf("%d\n", sizeof(fun1));
#elif (__WORDSIZE == 64)
    // printf("%ld\n", sizeof(long));
    printf("%ld\n", sizeof(ptrdiff_t));
    printf("%ld\n", sizeof(fun1));
#endif

    printf("%p\n", fun1);
    fun2(2, SIG_IGN);
    fun2(1, SIG_ERR);
    fun2(3, SIG_DFL);

    // signal(SIGPIPE, SIG_IGN); //实际这个函数的目的就是防止程序收到SIGPIPE后自动退出

    printf("gid is %d\n", getgid()); //返回组识别码，普通用户和root用户值不同
    printf("My parent pid = %d\n", getppid()); //返回父进程识别码

    pid_t child;

    //创建子进程
    if ((child = fork()) < 0) {
        printf("Fork Error: %s\n", strerror(errno));
        exit(1);
    } else if (child == 0) { //子进程
        signal(SIGPIPE, SIG_IGN);
        int i;
        printf("I am the child: %d\n", getpid());
        for (i = 0; i < 1000000; i++) {
            sin(i);
            // printf("I am alive -- %d\n", i);
        }
        printf("I exit with %d\n", i);
        exit(i);
    }

    signal(SIGCHLD, SIG_IGN);
    sleep(5);
    kill(child, SIGPIPE);

    return 0;
}