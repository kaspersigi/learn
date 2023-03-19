#include <stdio.h>

// 最后一条语句的值，将作为整个语句、语句块的值
#define getone() ({ 1; })
#define gettwice(x) ({ x * 2; })

// 实际上是类型转换
#define __pgd(x) ((pgd_t) { (x) })

int main(int argc, char* argv[])
{
    int a = getone();
    int b = gettwice(2);
    double c = gettwice(3.1415926);
    printf("a = %d\n", a);
    printf("b = %d\n", b);
    printf("c = %f\n", c);

    return 0;
}