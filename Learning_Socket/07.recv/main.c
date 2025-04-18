#include <arpa/inet.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#if 0 // 需要用到的函数和定义
// 创建套接字
// __domain 相应的AF地址族参数，当在计算机本地进程间通讯时，使用AF_UNIX或者AF_LOCAL，当使用跨主机网络通信时，使用AF_INET或者AF_INET6
// __type 网络传输协议 一般可选 SOCK_STREAM流式传输协议（其中最常见的TCP） SOCK_DGRAM报文传输协议（其中最常见的UDP）
// __protocol 协议，一般填0
// 返回值 成功则返回sockfd文件描述符，失败则返回-1或者错误码
int socket(int __domain, int __type, int __protocol);

// 绑定用于监听的socket和本地的ip端口
// 注：这里的参数ip也好，端口也好，都是大端的
// __fd 需要绑定的sockfd
// __addr socket结构体
// __len __addr socket结构体的大小，一般直接sizeof就行
// 返回值 成功则返回0，失败则返回-1或者错误码
int bind(int __fd, const struct sockaddr* __addr, socklen_t __len);

// ipv4 socket结构体
struct sockaddr {
    sa_family_t sa_family; //16位地址族协议 只能取AF_INET
    char sa_data[14]; //14字节地址数据，由16位端口号（2字节）+32位ip地址（4字节）+8字节填充数据
}; //该结构体不方便读取，因此一般使用struct sockaddr_in进行读写，再进行强制类型转换

// uint32_t 大端ipv4 ip地址
struct in_addr {
    in_addr_t s_addr;
};

// ipv4 socket结构体，大小与struct sockaddr完全一致
struct sockaddr_in {
    sa_family_t sin_family; //16位地址族协议 只能取AF_INET
    in_port_t sin_port; //16位端口号（2字节）
    struct in_addr sin_addr; //32位ip地址（4字节）
    unsigned char sin_zero[sizeof(struct sockaddr) - sizeof(sa_family_t) - sizeof(in_port_t) - sizeof(struct in_addr)]; //8字节填充数据
};

// ipv6 socket结构体
struct sockaddr_in6;

// 给监听的套接字设置监听
// __fd 要监听的sockfd
// __n 最大值128，同时能处理的最大连接要求
// 返回值 成功返回0 失败返回-1
int listen(int __fd, int __n);

// 等待并接受客户端的连接请求, 建立新的连接, 会得到一个新的文件描述符(通信的)
// __fd 监听的文件描述符
// __addr 出参，里边存储了建立连接的客户端的地址信息
// __addr_len 入参，用于存储__addr指向的内存大小
//  返回值 函数调用成功，得到一个文件描述符，用于和建立连接的这个客户端通信，调用失败返回-1
int accept(int __fd, struct sockaddr* __addr, socklen_t* __addr_len);

// 也可以使用文件IO函数read，只是recv函数多了__flags参数，一般填0
// 返回值 大于0则为实际接收到的字节的个数 为0则表示对方断开了连接 -1则为接收数据失败了
ssize_t recv(int __fd, void* __buf, size_t __n, int __flags);

// 关闭socket，此处就是文件IO中的close
int close(int __fd);

// 客户端只有一个通信sockfd
// 但是服务器端有多个sockfd，一个监听的sockfd，和多个通信的sockfd
// 和多少个客户端建立了连接，就有多少个通信sockfd

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
    int sockfd_service = accept(sockfd_listen, (struct sockaddr*)&sock_client, &sock_client_len);
    fputs("server connect succeed...\n", stdout);
    char read_buff[128] = {};
    int ret = recv(sockfd_service, read_buff, 128, 0);
    printf("server recieve %d charactors, content: %s\n", ret, read_buff);
    close(sockfd_service);
    close(sockfd_listen);

    return 0;
}