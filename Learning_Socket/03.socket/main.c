#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>

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
struct sockaddr_in6；
#endif

int main(int argc, char* argv[])
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in sock;
    sock.sin_family = AF_INET;
    sock.sin_port = htons(443);
    sock.sin_addr.s_addr = inet_addr("192.168.1.1");
    bind(sockfd, (struct sockaddr*)&sock, sizeof(sock));

    return 0;
}