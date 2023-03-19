#include <arpa/inet.h>
#include <stdio.h>

// u:unsigned
// 16: 16位, 32:32位
// h: host, 主机字节序，小端字序
// n: net, 网络字节序
// s: short
// l: long

// 由此可以组成多种函数
// 这套api主要用于网络通信过程中IP与端口的转换

#if 0 // 需要用到的函数和定义
// net->host short
uint16_t ntohs(uint16_t __netshort);

// net->host long
uint32_t ntohl(uint32_t __netlong);

// host->net short
uint16_t htons(uint16_t __hostshort);

// host->net long
uint32_t htonl(uint32_t __hostlong);
#endif

int main(int argc, char* argv[])
{
    uint16_t short_h1 = 2008;
    uint16_t short_n1 = htons(short_h1);
    printf("host short: %u, net short: %u\n", short_h1, short_n1);

    uint32_t long_h1 = 2008;
    uint32_t long_n1 = htonl(long_h1);
    printf("host long: %u, net long: %u\n", long_h1, long_n1);

    uint16_t short_n2 = 2008;
    uint16_t short_h2 = ntohs(short_n2);
    printf("net short: %u, host short: %u\n", short_n2, short_h2);

    uint32_t long_n2 = 2008;
    uint32_t long_h2 = ntohl(long_n2);
    printf("net long: %u, host long: %u\n", long_n2, long_h2);

    return 0;
}