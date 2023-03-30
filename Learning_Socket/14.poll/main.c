#define _POSIX_C_SOURCE 200809L
#include <arpa/inet.h>
#include <poll.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// poll的底层实现和select一样，用法也只是略有区别，但是不跨平台，不推荐使用

#if 0 // 需要用到的函数及定义
// __fds pollfd数组
// __nfds 监听的pollfd个数+1
// __timeout 超时时长，毫秒
// 返回值 revents事件的个数 错误返回-1和错误码
int poll(struct pollfd* __fds, nfds_t __nfds, int __timeout);

// fd 委托内核检测的文件描述符
// events 委托内核检测的事件，读事件 POLLIN、写事件 POLLOUT、异常事件 POLLERR。同时检测读写，则是 POLLIN | POLLOUT
// revents 文件描述符实际发生的事件
struct pollfd {
    int fd;
    short int events;
    short int revents;
};
#endif

int main(int argc, char* argv[])
{
    int sockfd_listen = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in sock_listen;
    sock_listen.sin_family = AF_INET;
    sock_listen.sin_port = htons(8888);
    sock_listen.sin_addr.s_addr = inet_addr("172.17.0.2");
    bind(sockfd_listen, (struct sockaddr*)&sock_listen, sizeof(sock_listen));
    listen(sockfd_listen, 128);
    struct sockaddr_in sock_client;
    socklen_t sock_client_len = sizeof(sock_listen);
    char read_buff[128] = {};

    int max_fd = 1;
    struct pollfd pollfds[1024] = {};
    for (int i = 0; i < 1024; ++i) {
        pollfds[i].fd = -1;
        pollfds[i].events = POLLIN;
    }
    pollfds[0].fd = sockfd_listen;

    while (1) {
        int ret = poll(pollfds, max_fd, 100);
        if (0 == ret) {
            continue;
        } else if (ret < 0) {
            fputs("poll error...\n", stderr);
            return ret;
        } else if (ret > 0) {
            if (pollfds[0].revents == POLLIN) {
                int sockfd_service = accept(sockfd_listen, (struct sockaddr*)&sock_client, &sock_client_len);
                pollfds[max_fd].fd = sockfd_service;
                pollfds[max_fd].events = POLLIN;
                max_fd++;
            }
            for (int i = 1; i < max_fd; ++i) {
                if (pollfds[i].revents == POLLIN) {
                    memset(read_buff, 0, 128);
                    int ret_read = recv(pollfds[i].fd, read_buff, 128, 0);
                    if (0 == ret_read) {
                        fputs("client disconnect...\n", stdout);
                        close(pollfds[i].fd);
                        pollfds[i].fd = -1;
                        break;
                    } else if (ret_read < 0) {
                        fputs("server read failed...\n", stderr);
                        break;
                    } else {
                        printf("server recieve %d charactors from client, content: %s\n", ret_read, read_buff);
                    }
                }
            }
        }
    }
    return 0;
}