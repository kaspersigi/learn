#include <arpa/inet.h>
#include <stdio.h>

// u:unsigned
// 16: 16位, 32:32位
// h: host, 主机字节序，小端字序
// n: net, 网络字节序
// s: short
// l: long

// 由此可以组成多种函数
// 这套api主要用于将主机端的IP地址转换为网络字节序
// 主机字节序的IP地址是字符串，网络字节序的IP地址是整型

#if 0 // 需要用到的函数和定义
// 将主机端的IP地址转换为网络字节序
// __af 地址族 AF_INET ipv4格式的ip地址 AF_INET6 ipv6格式的ip地址
// __cp 入参 对应要转换的点分十进制的ip地址 如："192.168.1.1"
// __buf 出参 函数调用完成，得到的大端整型IP被写到这块内存
// 返回值 成功返回1 失败返回0或者-1
int inet_pton(int __af, const char* __restrict__ __cp, void* __restrict__ __buf);

// 将网络字节序的大端整型IP转换为主机端的字符串
// __af 地址族 AF_INET ipv4格式的ip地址 AF_INET6 ipv6格式的ip地址
// __cp 入参 对应内存中存储了的大端整型IP地址
// __buf 出参 函数调用完成，转换得到的小端的点分十进制的IP地址
// __len 修饰__buf参数的，标记__buf指向的内存中最多可以存储多少个字节
// 返回值 成功返回指针指向__buf对应的内存地址 失败返回0或者-1
char* inet_ntop(int __af, const void* __restrict __cp, char* __restrict __buf, socklen_t __len);

//下面一组函数也可以进行IP地址的转换，但是只能处理ipv4的地址
// 点分十进制IP -> 大端整形
in_addr_t inet_addr(const char* __cp);

// 大端整形 -> 点分十进制IP
char* inet_ntoa(struct in_addr __in);

struct sockaddr {
    sa_family_t sa_family; // 地址族协议, ipv4
    char sa_data[14]; // 端口(2字节) + IP地址(4字节) + 填充(8字节)
};
#endif

int main(int argc, char* argv[])
{
    uint32_t ipv4_nl;
    int ret = inet_pton(AF_INET, "192.168.1.1", &ipv4_nl);
    if (ret != 1) {
        fputs("inet_pton failed...\n", stderr);
        return -1;
    }

    char ipv4_h[16] = {};
    const char* cret = inet_ntop(AF_INET, &ipv4_nl, ipv4_h, 16);
    if (cret == 0 || ret == -1) {
        fputs("inet_ntop failed...\n", stderr);
        return -1;
    }
    printf("%s\n", ipv4_h);

    return 0;
}