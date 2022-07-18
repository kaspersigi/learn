#include "threadpool.h"
#include <arpa/inet.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static const char host[] = "172.17.0.2";
static const uint32_t port = 8888;
#define BUFFER_SIZE 128

typedef struct sock_info {
    struct sockaddr_in sock_client;
    int sockfd_service;
} sock_info;

void* service(void* arg)
{
    sock_info myarg = *(sock_info*)arg;
    struct sockaddr_in sock_client = myarg.sock_client;
    int sockfd_service = myarg.sockfd_service;
    const char* client_ip = inet_ntoa(sock_client.sin_addr);
    char read_buff[BUFFER_SIZE] = {};
    while (1) {
        memset(read_buff, 0, BUFFER_SIZE);
        int ret_read = recv(sockfd_service, read_buff, BUFFER_SIZE, 0);
        if (0 == ret_read) {
            fputs("client disconnect...\n", stdout);
            break;
        } else if (ret_read < 0) {
            fputs("server read failed...\n", stderr);
            break;
        } else {
            printf("server recieve %d charactors from client %s, content: %s\n", ret_read, client_ip, read_buff);
        }
    }
    printf("%s: %s, pid: %d, tid: %lx, child thread is closing..\n", __PRETTY_FUNCTION__, "child thread", getpid(), pthread_self());
    close(sockfd_service);
    return NULL;
}

int main(int argc, char* argv[])
{
    pid_t pid = getpid();
    pthread_t tid_main = pthread_self();
    printf("%s: %s, pid: %d, tid: %lx, is starting...\n", __PRETTY_FUNCTION__, "main thread", pid, tid_main);
    ThreadPool* threadpool = threadpool_create(3, 10, 100);

    int sockfd_listen = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd_listen < 0) {
        fputs("create listen sockfd failed!\n", stderr);
        return sockfd_listen;
    }
    struct sockaddr_in sock_listen;
    sock_listen.sin_family = AF_INET;
    sock_listen.sin_port = htons(port);
    sock_listen.sin_addr.s_addr = inet_addr(host);
    int ret_bind = bind(sockfd_listen, (struct sockaddr*)&sock_listen, sizeof(sock_listen));
    if (ret_bind < 0) {
        fputs("bind sockfd failed!\n", stderr);
        return ret_bind;
    }
    int ret_listen = listen(sockfd_listen, BUFFER_SIZE);
    if (ret_listen < 0) {
        fputs("create listen sockfd failed!\n", stderr);
        return ret_listen;
    }

    while (1) {
        struct sockaddr_in sock_client;
        socklen_t sock_client_len = sizeof(sock_listen);
        int sockfd_service = accept(sockfd_listen, (struct sockaddr*)&sock_client, &sock_client_len);
        if (sockfd_service < 0) {
            fputs("server accept failed!\n", stdout);
            // return sockfd_service;
            break;
        } else {
            fputs("server connect succeed...\n", stdout);
            pthread_t tid_service;
            printf("%s: %s, pid: %d, tid: %lx, prepare creating new thread...\n", __PRETTY_FUNCTION__, "main thread", pid, tid_main);
            // 有个小问题，传给子线程的，只有sockfd_service，没有sock_client
            // 没拿到客户端的ip和端口，不方便做更多的事情
            // 因此 新建一个结构体，把sockfd_service和sock_client都传进去
            sock_info* arg = malloc(sizeof(sock_info));
            arg->sockfd_service = sockfd_service;
            arg->sock_client = sock_client;
            threadpool_add(threadpool, service, (void*)arg);
            // pthread_create(&tid_service, NULL, service, (void*)&sockfd_service);
        }
    }
    close(sockfd_listen);
    fputs("server close...\n", stdout);
    threadpool_destroy(threadpool);
    return 0;
}