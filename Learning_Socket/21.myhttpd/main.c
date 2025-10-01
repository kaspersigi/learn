#define _POSIX_C_SOURCE 200809L

#include <arpa/inet.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const char server_string[] = "server: myhttpd/0.1.0\r\n";
static const char host[] = "127.0.0.1";
static const uint32_t port = 8888;
static const int buffer_size = 1024;

int start()
{
    int sockfd_listen = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd_listen < 0) {
        perror("create listen sockfd faild");
        return -1;
    }
    struct sockaddr_in sock_listen;
    sock_listen.sin_family = AF_INET;
    sock_listen.sin_port = htons(port);
    sock_listen.sin_addr.s_addr = inet_addr(host);
    int ret = bind(sockfd_listen, (struct sockaddr*)&sock_listen, sizeof(sock_listen));
    if (ret < 0) {
        perror("bind listen sockfd faild");
        return -1;
    }
    ret = listen(sockfd_listen, 128);
    if (ret < 0) {
        perror("set listen faild");
        return -1;
    }
    return sockfd_listen;
}

int read_line(int sockfd_service, char* buf, int size)
{
    char ch = '\0';
    char last = '\0';
    int pos = 0;
    for (int i = 0; i < size; ++i) {
        int ret = recv(sockfd_service, &ch, 1, 0);
        if (ret == 0) {
            printf("client disconnect...\n");
            break;
        } else if (ret < 0) {
            perror("recieve faild");
            return -1;
        } else {
            if (last == '\r' && ch == '\n') {
                buf[pos] = '\n';
                ++pos;
            } else if (ch == '\r') {
                last = ch;
            } else {
                buf[pos] = ch;
                ++pos;
                last = ch;
            }
        }
    }
    buf[pos] = '\0';
    return pos;
}

void* accept_request(void* arg)
{
    int sockfd_service = *(int*)arg;
    char buf[buffer_size];
    memset(buf, 0, buffer_size);
    bool use_cgi = false;

    char method[255] = { 0 };
    char url[255] = { 0 };
    char path[512] = { 0 };

    int ret = read_line(sockfd_service, buf, buffer_size);
    if (ret > 0) {
        write(1, buf, ret);
    }

    close(sockfd_service);
    printf("free sockfd_service\n");
    return NULL;
}

void bad_request(int sockfd_service)
{
    char buf[buffer_size];
    memset(buf, 0, buffer_size);

    sprintf(buf, "HTTP/1.1 400 BAD REQUEST\r\n");
    send(sockfd_service, buf, sizeof(buf), 0);
    sprintf(buf, "Content-type: text/html\r\n");
    send(sockfd_service, buf, sizeof(buf), 0);
    sprintf(buf, "\r\n");
    send(sockfd_service, buf, sizeof(buf), 0);
    sprintf(buf, "<P>Your browser sent a bad request, ");
    send(sockfd_service, buf, sizeof(buf), 0);
    sprintf(buf, "such as a POST without a Content-Length.\r\n");
    send(sockfd_service, buf, sizeof(buf), 0);
}

void cannot_execute(int sockfd_service)
{
    char buf[buffer_size];
    memset(buf, 0, buffer_size);

    sprintf(buf, "HTTP/1.1 500 Internal Server Error\r\n");
    send(sockfd_service, buf, strlen(buf), 0);
    sprintf(buf, "Content-type: text/html\r\n");
    send(sockfd_service, buf, strlen(buf), 0);
    sprintf(buf, "\r\n");
    send(sockfd_service, buf, strlen(buf), 0);
    sprintf(buf, "<P>Error prohibited CGI execution.\r\n");
    send(sockfd_service, buf, strlen(buf), 0);
}

void headers(int sockfd_service)
{
    char buf[buffer_size];
    memset(buf, 0, buffer_size);

    strcpy(buf, "HTTP/1.1 200 OK\r\n");
    send(sockfd_service, buf, strlen(buf), 0);
    strcpy(buf, server_string);
    send(sockfd_service, buf, strlen(buf), 0);
    sprintf(buf, "Content-Type: text/html\r\n");
    send(sockfd_service, buf, strlen(buf), 0);
    strcpy(buf, "\r\n");
    send(sockfd_service, buf, strlen(buf), 0);
}

void not_found(int sockfd_service)
{
    char buf[buffer_size];
    memset(buf, 0, buffer_size);

    sprintf(buf, "HTTP/1.1 404 NOT FOUND\r\n");
    send(sockfd_service, buf, strlen(buf), 0);
    sprintf(buf, server_string);
    send(sockfd_service, buf, strlen(buf), 0);
    sprintf(buf, "Content-Type: text/html\r\n");
    send(sockfd_service, buf, strlen(buf), 0);
    sprintf(buf, "\r\n");
    send(sockfd_service, buf, strlen(buf), 0);
    sprintf(buf, "<HTML><TITLE>Not Found</TITLE>\r\n");
    send(sockfd_service, buf, strlen(buf), 0);
    sprintf(buf, "<BODY><P>The server could not fulfill\r\n");
    send(sockfd_service, buf, strlen(buf), 0);
    sprintf(buf, "your request because the resource specified\r\n");
    send(sockfd_service, buf, strlen(buf), 0);
    sprintf(buf, "is unavailable or nonexistent.\r\n");
    send(sockfd_service, buf, strlen(buf), 0);
    sprintf(buf, "</BODY></HTML>\r\n");
    send(sockfd_service, buf, strlen(buf), 0);
}

void unimplemented(int sockfd_service)
{
    char buf[buffer_size];
    memset(buf, 0, buffer_size);

    sprintf(buf, "HTTP/1.1 501 Method Not Implemented\r\n");
    send(sockfd_service, buf, strlen(buf), 0);
    sprintf(buf, server_string);
    send(sockfd_service, buf, strlen(buf), 0);
    sprintf(buf, "Content-Type: text/html\r\n");
    send(sockfd_service, buf, strlen(buf), 0);
    sprintf(buf, "\r\n");
    send(sockfd_service, buf, strlen(buf), 0);
    sprintf(buf, "<HTML><HEAD><TITLE>Method Not Implemented\r\n");
    send(sockfd_service, buf, strlen(buf), 0);
    sprintf(buf, "</TITLE></HEAD>\r\n");
    send(sockfd_service, buf, strlen(buf), 0);
    sprintf(buf, "<BODY><P>HTTP request method not supported.\r\n");
    send(sockfd_service, buf, strlen(buf), 0);
    sprintf(buf, "</BODY></HTML>\r\n");
    send(sockfd_service, buf, strlen(buf), 0);
}

int main(int argc, char* argv[])
{
    int sockfd_listen = start();
    if (sockfd_listen < 0) {
        return -1;
    }
    printf("httpd running on port %d\n", port);
    struct sockaddr_in sock_client;
    socklen_t sock_client_len = sizeof(sock_client);

    while (1) {
        int sockfd_service = accept(sockfd_listen, (struct sockaddr*)&sock_client, &sock_client_len);
        if (sockfd_service < 0) {
            perror("accept faild");
            return -1;
        }
        accept_request((void*)&sockfd_service);
        // pthread_t child_tid;
        // pthread_create(&child_tid, NULL, accept_request, (void*)&sockfd_service);
    }

    close(sockfd_listen);
    printf("free sockfd_listen\n");
    pthread_exit(0);
}

// http://127.0.0.1:8888/index.html