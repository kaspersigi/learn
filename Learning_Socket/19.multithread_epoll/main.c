#define _POSIX_C_SOURCE 200809L

#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <unistd.h>

static const char host[] = "172.17.0.2";
static const uint32_t port = 8888;
static const int buffer_size = 5;
atomic_int max_fd = 1;

typedef struct epoll_info {
    int epfd;
    struct epoll_event epoll_event;
} epoll_info;

void* service(void* arg)
{
    pthread_detach(pthread_self());
    char* read_buff = malloc(buffer_size);
    char* host_buff = malloc(4096);
    int epfd = ((epoll_info*)arg)->epfd;
    struct epoll_event epoll_event = ((epoll_info*)arg)->epoll_event;
    printf("%s: %s, pid: %d, tid: %lx, child thread is serving...\n", __PRETTY_FUNCTION__, "child thread", getpid(), pthread_self());
    memset(host_buff, 0, 4096);
    size_t pos = 0;
    while (1) {
        memset(read_buff, 0, buffer_size);
        size_t ret_read = recv(epoll_event.data.fd, read_buff, buffer_size, 0);
        if (0 == ret_read) {
            printf("client disconnect...\n");
            int ret = epoll_ctl(epfd, EPOLL_CTL_DEL, epoll_event.data.fd, NULL);
            close(epoll_event.data.fd);
            if (ret < 0) {
                perror("epoll_ctl faild");
                return (void*)-1;
            }
            atomic_fetch_sub(&max_fd, 1);
            break;
        } else if (ret_read < 0) {
            if (errno == EAGAIN) {
                printf("server recieve %d bytes from client, content: %s\n", pos + 1, host_buff);
                break;
            }
            perror("revieve faild");
            break;
        } else {
            if (pos + ret_read < 4096) {
                memcpy(host_buff + pos, read_buff, ret_read);
                pos += ret_read;
            } else if (pos < 4096) {
                memcpy(host_buff + pos, read_buff, 4096 - pos);
                pos = 4096;
            }
        }
    }
    printf("%s: %s, pid: %d, tid: %lx, child thread is exiting...\n", __PRETTY_FUNCTION__, "child thread", getpid(), pthread_self());
    free(read_buff);
    free(host_buff);
    return NULL;
}

int main(int argc, char* argv[])
{
    int ret;
    pid_t pid = getpid();
    pthread_t tid_main = pthread_self();
    pthread_t tid_child;
    printf("%s: %s, pid: %d, tid: %lx, running...\n", __PRETTY_FUNCTION__, "main thread", pid, tid_main);

    int sockfd_listen = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd_listen < 0) {
        perror("create listen sockfd faild");
        return -1;
    }
    struct sockaddr_in sock_listen;
    sock_listen.sin_family = AF_INET;
    sock_listen.sin_port = htons(port);
    sock_listen.sin_addr.s_addr = inet_addr(host);
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

    int epfd = epoll_create(1);
    if (epfd < 0) {
        perror("epoll_create faild");
        return -1;
    }

    struct epoll_event epoll_event_listen;

    epoll_event_listen.events = EPOLLIN | EPOLLET;
    epoll_event_listen.data.fd = sockfd_listen;

    struct epoll_event epoll_event_list[1024] = {};

    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, epoll_event_listen.data.fd, &epoll_event_listen);
    if (ret < 0) {
        perror("epoll_ctl faild");
        return -1;
    }
    while (1) {
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

                    int flag = fcntl(sockfd_service, F_GETFL);
                    flag |= O_NONBLOCK;
                    fcntl(sockfd_service, F_SETFL, flag);
                    struct epoll_event epoll_event_service;

                    epoll_event_service.events = EPOLLIN | EPOLLET;
                    epoll_event_service.data.fd = sockfd_service;

                    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, epoll_event_service.data.fd, &epoll_event_service);
                    if (ret < 0) {
                        perror("epoll_ctl faild");
                        return -1;
                    }
                    printf("connect client succeed...\n");
                    atomic_fetch_add(&max_fd, 1);
                } else if (epoll_event_list[i].events == EPOLLIN) {
                    epoll_info arg;
                    arg.epfd = epfd;
                    arg.epoll_event = epoll_event_list[i];
                    printf("%s: %s, pid: %d, tid: %lx, prepare creating thread...\n", __PRETTY_FUNCTION__, "main thread", pid, tid_main);
                    pthread_create(&tid_child, NULL, service, (void*)&arg);
                }
            }
        }
    }
    close(epfd);
    pthread_exit(0);
}