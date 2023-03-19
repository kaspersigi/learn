#include <stdio.h>

union endian {
    char c[4];
    int i;
};

int main(int argc, char* argv[])
{
    union endian data;
    data.c[0] = 0x04;
    data.c[1] = 0x03;
    data.c[2] = 0x02;
    data.c[3] = 0x01;
    printf("0%x\n", data.i);

    return 0;
}

// 1020304
// intel、arm芯片都是小端方案，网络是大端方案
// 小端方案：数据的低位字节存储到内存的低地址位，数据的高位字节存储到内存的高地址位
// 大端方案：数据的低位字节存储到内存的高地址位，数据的高位字节存储到内存的低地址位