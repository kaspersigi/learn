#define _POSIX_C_SOURCE 200809L

#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

// IO多路复用 主要有 select poll epoll
// select可以跨平台使用
// poll epoll仅限类unix平台使用
// 关于三者的效率，select和poll的底层实现是线性表，epoll的底层实现是红黑树
// select检测上限1024个，epoll不限
// 因此select效率最低，epoll效率最高，所以一般要么使用select要么使用epoll

// IO多路复用，其实是把检测多个fd的读写缓冲区的任务交给了内核进行处理
// 与多进程、多线程技术相比，IO多路复用技术最大的优势就是系统开销小，系统不必创建进程/线程，也不用维护这些进程/线程，从而大大减小了系统的开销

#if 0 // 需要用到的函数及定义
// __nfds 委托内核检测的三大集合中的最大文件描述符+1，最大值为1024（即一般条件下，一个进程的文件描述符范围为0~1023）因为select的底层实现是线性表。所以需要指定一个遍历的终止位置，windows下这个参数无意义，填-1即可
// __readfds 文件描述符集合，内核只检测集合中文件描述符的读缓冲区，如果不需要使用，可以指定为NULL，例如：[5,6,7,8]
// __writefds 文件描述符集合，内核只检测集合中文件描述符的写缓冲区，如果不需要使用，可以指定为NULL，例如：[5,6,7,8]
// __exceptfds 文件描述符集合，不检测文件描述符的读写缓冲区，内核只检测集合中文件描述符是否产生异常，例如：[5,6,7,8,9,10]
// __timeout 超时时长，select检测多长时间内的文件描述符集合的变化，如果设定时间内没有状态变化，则响应时间后返回，如果设定时间内发生变化，则在变化后返回，如果设置为0，则相当于不阻塞，只检测一次，检测完即返回
// fd_set* 1024bit 占用空间1024/8=128Byte，int型的话，就是128/4=32，所以fd_set*其实就是int fd_set[32]
// 返回值为三个集合中，所有满足条件的（就绪的）文件描述符的个数，-1表示有异常
// 内核同时检测三个文件描述符集合，当检测的文件描述符状态改变时，将发生变化的文件描述符的集合，写入相应的缓存，所以__readfds，__writefds，__exceptfds既是入参也是出参
int select(int __nfds, fd_set* __restrict__ __readfds, fd_set* __restrict__ __writefds, fd_set* __restrict__ __exceptfds, struct timeval* __restrict__ __timeout);

// 时间结构体
// tv_sec 秒
// tv_usec 微秒
struct timeval {
    __time_t tv_sec; /* Seconds.  */
    __suseconds_t tv_usec; /* Microseconds.  */
};

// 四组用于设置文件描述符集合fd_set*的函数
// 将文件描述符fd从集合set中删除（将1024bit中相应的bit位置为0
void FD_CLR(int fd, fd_set* set);
// 判断文件描述符是否在集合set中
int FD_ISSET(int fd, fd_set* set);
// 将文件描述符fd插入到集合set中（将1024bit中相应的bit位置为1
void FD_SET(int fd, fd_set* set);
// 初始化函数，将集合set中所有bit位置0
void FD_ZERO(fd_set* set);
#endif

int main(int argc, char* argv[])
{
    int sockfd_listen = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd_listen < 0) {
        return -1;
    }
    struct sockaddr_in sock_listen;
    sock_listen.sin_family = AF_INET;
    sock_listen.sin_port = htons(8888);
    sock_listen.sin_addr.s_addr = inet_addr("172.17.0.2");
    bind(sockfd_listen, (struct sockaddr*)&sock_listen, sizeof(sock_listen));
    listen(sockfd_listen, 128);
    struct sockaddr_in sock_client;
    socklen_t sock_client_len = sizeof(sock_listen);
    char read_buff[128] = {};

    fd_set readfd_set, nextfd_set;
    struct timeval listen_timeval = { 5, 0 };

    FD_ZERO(&readfd_set);
    FD_ZERO(&nextfd_set);
    FD_SET(sockfd_listen, &nextfd_set);
    while (1) {
        readfd_set = nextfd_set;
        int ret = select(1024, &readfd_set, NULL, NULL, &listen_timeval);
        if (ret < 0) {
            fputs("select error...\n", stderr);
            return ret;
        } else if (0 == ret) {
            continue;
        } else {
            for (int i = 0, count = 0; i < 1024 && count < ret; ++i) {
                if (FD_ISSET(i, &readfd_set)) {
                    count++;
                    if (i == sockfd_listen) {
                        int sockfd_service = accept(sockfd_listen, (struct sockaddr*)&sock_client, &sock_client_len);
                        fputs("server connect succeed...\n", stdout);
                        FD_SET(sockfd_service, &nextfd_set);
                    } else {
                        memset(read_buff, 0, 128);
                        int ret_read = recv(i, read_buff, 128, 0);
                        if (0 == ret_read) {
                            fputs("client disconnect...\n", stdout);
                            close(i);
                            FD_CLR(i, &nextfd_set);
                            break;
                        } else if (ret_read < 0) {
                            fputs("server read failed...\n", stderr);
                            FD_CLR(i, &nextfd_set);
                            break;
                        } else {
                            printf("server recieve %d charactors from client, content: %s\n", ret_read, read_buff);
                            FD_SET(i, &nextfd_set);
                        }
                    }
                }
            }
        }
    }
    close(sockfd_listen);

    return 0;
}