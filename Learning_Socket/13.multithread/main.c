#define _POSIX_C_SOURCE 200809L
#include <arpa/inet.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <sys/select.h>
#include <unistd.h>

static const char host[] = "172.17.0.2";
static const uint32_t port = 8888;
static const int buffer_size = 128;

static fd_set nextfd_set;
pthread_mutex_t sockfd_service_mutex;

typedef struct sock_info {
    struct sockaddr_in sock_client;
    int sockfd_service;
} sock_info;

void* service(void* arg)
{
    pthread_detach(pthread_self());
    printf("%s: %s, pid: %d, tid: %lx, child thread is serving...\n", __PRETTY_FUNCTION__, "child thread", getpid(), pthread_self());
    sock_info myarg = *(sock_info*)arg;
    struct sockaddr_in sock_client = myarg.sock_client;
    int sockfd_service = myarg.sockfd_service;
    const char* client_ip = inet_ntoa(sock_client.sin_addr);
    char read_buff[buffer_size];
    while (1) {
        memset(read_buff, 0, buffer_size);
        size_t ret_read = recv(sockfd_service, read_buff, buffer_size, 0);
        if (0 == ret_read) {
            fputs("client disconnect...\n", stdout);
            break;
        } else if (ret_read < 0) {
            fputs("server read failed...\n", stderr);
            break;
        } else {
            printf("server recieve %lu charactors from client %s, content: %s\n", ret_read, client_ip, read_buff);
        }
    }
    printf("%s: %s, pid: %d, tid: %lx, child thread is closing..\n", __PRETTY_FUNCTION__, "child thread", getpid(), pthread_self());
    close(sockfd_service);
    pthread_mutex_trylock(&sockfd_service_mutex);
    FD_CLR(sockfd_service, &nextfd_set);
    pthread_mutex_unlock(&sockfd_service_mutex);
    return NULL;
}

int main(int argc, char* argv[])
{
    pid_t pid = getpid();
    pthread_t tid_main = pthread_self();
    printf("%s: %s, pid: %d, tid: %lx, running...\n", __PRETTY_FUNCTION__, "main thread", pid, tid_main);
    int sockfd_listen = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd_listen < 0) {
        fputs("create listen sockfd failed!\n", stderr);
        return sockfd_listen;
    }
    printf("sockfd_listen = %d\n", sockfd_listen);
    struct sockaddr_in sock_listen;
    sock_listen.sin_family = AF_INET;
    sock_listen.sin_port = htons(port);
    sock_listen.sin_addr.s_addr = inet_addr(host);
    int ret_bind = bind(sockfd_listen, (struct sockaddr*)&sock_listen, sizeof(sock_listen));
    if (ret_bind < 0) {
        fputs("bind sockfd failed!\n", stderr);
        return ret_bind;
    }
    listen(sockfd_listen, 128);
    struct sockaddr_in sock_client;
    socklen_t sock_client_len = sizeof(sock_listen);

    pthread_mutex_init(&sockfd_service_mutex, NULL);

    struct timeval listen_timeval = { 5, 0 };
    fd_set servicefd_set;
    FD_ZERO(&servicefd_set);
    FD_ZERO(&nextfd_set);
    FD_SET(sockfd_listen, &nextfd_set);
    while (1) {
        pthread_mutex_trylock(&sockfd_service_mutex);
        servicefd_set = nextfd_set;
        pthread_mutex_unlock(&sockfd_service_mutex);
        int ret = select(1024, &servicefd_set, NULL, NULL, &listen_timeval);
        if (ret < 0) {
            fputs("select error...\n", stderr);
            printf("ret = %d\n", ret);
            return ret;
        } else if (0 == ret) {
            continue;
        } else {
            for (int i = 3, count = 0; i < 1024 && count < ret; ++i) {
                if (FD_ISSET(i, &servicefd_set)) {
                    count++;
                    if (i == sockfd_listen) {
                        pthread_t tid_service;
                        int sockfd_service = accept(sockfd_listen, (struct sockaddr*)&sock_client, &sock_client_len);
                        if (sockfd_service < 0) {
                            fputs("server accept failed!\n", stdout);
                            // return sockfd_service;
                            break;
                        } else {
                            fputs("server connect succeed...\n", stdout);
                            printf("new sockfd_service = %d\n", sockfd_service);
                            FD_SET(sockfd_service, &nextfd_set);
                            sock_info arg = { sock_client, sockfd_service };
                            printf("%s: %s, pid: %d, tid: %lx, prepare creating new thread...\n", __PRETTY_FUNCTION__, "main thread", pid, tid_main);
                            pthread_create(&tid_service, NULL, service, (void*)&arg);
                        }
                    }
                }
            }
        }
    }

    pthread_exit(0);
    pthread_mutex_destroy(&sockfd_service_mutex);
    close(sockfd_listen);
    fputs("server close...\n", stdout);

    return 0;
}