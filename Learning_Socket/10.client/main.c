#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    int sockfd_client = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd_client < 0) {
        perror("create client sockfd faild");
        return -1;
    }
    struct sockaddr_in sock_server;
    sock_server.sin_family = AF_INET;
    sock_server.sin_port = htons(8888);
    sock_server.sin_addr.s_addr = inet_addr("172.17.0.2");
    int ret = connect(sockfd_client, (struct sockaddr*)&sock_server, sizeof(sock_server));
    if (ret < 0) {
        perror("connect faild");
        return -1;
    }
    fputs("client connect succeed...\n", stdout);
    char write_head[] = "Hello server, I am client!";
    char write_buff[128] = {};
    for (int i = 0; i < 60; ++i) {
        memset(write_buff, 0, 128);
        sprintf(write_buff, "%s count: %d", write_head, i);
        int ret_write = send(sockfd_client, write_buff, strlen(write_buff), 0);
        if (0 == ret_write) {
            fputs("server disconnect...\n", stdout);
            break;
        } else if (ret_write < 0) {
            perror("send faild");
            return -1;
        } else {
            printf("client send %d bytes, content: %s\n", ret_write, write_buff);
        }
        sleep(1);
    }
    close(sockfd_client);

    return 0;
}