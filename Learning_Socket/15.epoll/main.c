#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/epoll.h>
#include <unistd.h>

// select和poll的对比
// select和poll这种io多路转接，可以用单线程实现多并发，提高程序运行效率
// 缺点：
// 1、select监测有三个集合，频繁在用户区和内核区进行数据拷贝，效率低
// 2、内核对select的集合是线性遍历的，如果待检测的文件描述符很多，效率比较低。反之，待检测的文件描述符很少，则效率比较高
// 3、select最多只能检测1024个文件描述符

// epoll全称eventpoll，是select和poll的升级版
// epoll维护的不仅仅是fd集合，还包含了fd的操作函数，也就是回调机制，整体相当于事件处理机制，相应fd的事件发生，就调用相应的回调函数

// epoll和select、poll的区别
// select和poll对待检测集合是线性处理的，epoll是基于红黑树
// select和poll每次都会线性扫描整个待检测集合，集合越大速度越慢，epoll使用的是回调机制，效率高，处理效率也不会随着检测集合的变大而下降
// select和poll工作过程中存在内核、用户空间数据的频繁拷贝问题，在epoll中内核和用户区使用的是共享内存（基于mmap内存映射区实现），省去了不必要的内存拷贝
// 程序猿需要对select和poll返回的集合进行判断才能知道哪些文件描述符是就绪的，通过epoll可以直接得到已就绪的文件描述符集合，无需再次检测
// 使用epoll没有最大文件描述符的限制，仅受系统中进程能打开的最大文件数目限制 当多路复用的文件数量庞大、IO流量频繁的时候，一般不太适合使用select()和poll()，这种情况下select()和poll()表现较差，推荐使用 epoll()

#if 0 // 需要用到的函数及定义
// 创建epoll实例，通过一棵红黑树管理待检测集合
// __size填入任何大于0的整数即可，会被忽略
// 返回值 成功则为创建的epoll的实例的文件描述符epfd，失败则返回-1或错误码
int epoll_create(int __size);

// 管理红黑树上的文件描述符(添加、修改、删除)
// __epfd epoll实例的文件描述符
// __op 对epoll实例进行的操作，可填EPOLL_CTL_ADD 添加需要检测的文件描述符、EPOLL_CTL_MOD 修改已经添加的文件描述符（的事件）、EPOLL_CTL_DEL 删除已经添加的文件描述符
// __fd 要操作的文件描述符
// __event 和__op、__fd对应的事件
int epoll_ctl(int __epfd, int __op, int __fd, struct epoll_event* __event);

// 检测epoll树中是否有就绪的文件描述符
// __epfd 入参，epoll实例的文件描述符
// __event 出参，事件数组，存储了已就绪的文件描述符的信息
// __maxevents __event数组中事件的个数
// __timeout 入参，如果检测的epoll实例中没有已就绪的文件描述符，该函数阻塞的时长，单位：毫秒，如果__timeout为0：函数不阻塞，不管epoll实例中有没有就绪的文件描述符，函数被调用后都直接返回。如果__timeout大于0：如果epoll实例中没有已就绪的文件描述符，函数阻塞对应的毫秒数再返回。如果__timeout为-1：函数一直阻塞，直到epoll实例中有已就绪的文件描述符之后才解除阻塞
// 返回值 等于0：函数是阻塞被强制解除了，没有检测到满足条件的文件描述符。大于0：检测到的已就绪的文件描述符的总个数。失败：返回-1或错误码
int epoll_wait(int __epfd, struct epoll_event* __events, int __maxevents, int __timeout);

// epoll事件结构体
// events epoll事件 可选事件很多，这里填几个常用的事件EPOLLIN 检测文件描述符的读事件，EPOLLOUT 检测文件描述符的写事件（注意：只要文件描述符写就绪，可写，就会触发），EPOLLERR 检测文件描述符的错误事件，EPOLLET epoll默认触发模式为水平触发模式，使用这个可以将其设置为边沿触发模式
// data 传入传出参数，用户设置相应的数值，如果相应的事件触发了，传出时指定的数值依然为用户设置的数值，相当于对事件的备注信息
struct epoll_event {
    uint32_t events;
    epoll_data_t data;
};

// epoll_data联合体
// 一般使用第二个 fd
typedef union epoll_data {
    void* ptr;
    int fd;
    uint32_t u32;
    uint64_t u64;
} epoll_data_t;
#endif

int main(int argc, char* argv[])
{
    int ret;
    int sockfd_listen = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd_listen < 0) {
        perror("create listen sockfd faild");
        return -1;
    }
    struct sockaddr_in sock_listen;
    sock_listen.sin_family = AF_INET;
    sock_listen.sin_port = htons(8888);
    sock_listen.sin_addr.s_addr = inet_addr("172.17.0.2");
    ret = bind(sockfd_listen, (struct sockaddr*)&sock_listen, sizeof(sock_listen));
    if (ret < 0) {
        perror("bind listen sockfd faild");
        return -1;
    }
    ret = listen(sockfd_listen, 128);
    if (ret < 0) {
        perror("set listen faild");
        return -1;
    }
    struct sockaddr_in sock_client;
    socklen_t sock_client_len = sizeof(sock_listen);
    char read_buff[128] = {};

    int epfd = epoll_create(1);
    if (epfd < 0) {
        perror("epoll_create faild");
        return -1;
    }

    struct epoll_event epoll_event_listen;
    epoll_event_listen.events = EPOLLIN;
    epoll_event_listen.data.fd = sockfd_listen;
    struct epoll_event epoll_event_list[1024] = {};

    for (int i = 0; i < 1024; ++i) {
        epoll_event_list[i].events = EPOLLIN;
        epoll_event_list[i].data.fd = -1;
    }

    int max_fd = 1;
    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, epoll_event_listen.data.fd, &epoll_event_listen);
    if (ret < 0) {
        perror("epoll_ctl faild");
        return -1;
    }

    while (1) {
        // epoll_wait的第二个参数是纯出参，是相较select、poll很大的差别
        int count = epoll_wait(epfd, epoll_event_list, max_fd, -1);
        if (count < 0) {
            perror("epoll_wait faild");
            return -1;
        } else if (0 == count) {
            continue;
        } else {
            for (int i = 0; i < count; ++i) {
                if (epoll_event_list[i].data.fd == sockfd_listen && epoll_event_list[i].events == EPOLLIN) {
                    int sockfd_service = accept(sockfd_listen, (struct sockaddr*)&sock_client, &sock_client_len);
                    if (sockfd_service < 0) {
                        perror("accept faild");
                        return -1;
                    }
                    struct epoll_event epoll_event_service;
                    epoll_event_service.events = EPOLLIN;
                    epoll_event_service.data.fd = sockfd_service;

                    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, epoll_event_service.data.fd, &epoll_event_service);
                    if (ret < 0) {
                        perror("epoll_ctl faild");
                        return -1;
                    }
                    max_fd++;
                } else if (epoll_event_list[i].events == EPOLLIN) {
                    memset(read_buff, 0, 128);
                    int ret_read = recv(epoll_event_list[i].data.fd, read_buff, 128, 0);
                    if (0 == ret_read) {
                        fputs("client disconnect...\n", stdout);
                        ret = epoll_ctl(epfd, EPOLL_CTL_DEL, epoll_event_list[i].data.fd, NULL);
                        close(epoll_event_list[i].data.fd);
                        if (ret < 0) {
                            perror("epoll_ctl faild");
                            return -1;
                        }
                        max_fd--;
                    } else if (ret_read < 0) {
                        perror("revieve faild");
                        break;
                    } else {
                        printf("server recieve %d charactors from client, content: %s\n", ret_read, read_buff);
                    }
                }
            }
        }
    }

    close(epfd);
    return 0;
}