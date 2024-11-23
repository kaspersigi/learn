#include <stdio.h>

typedef int (*func)(int a, int b);

int add(int a, int b)
{
    return a + b;
}

int main(int argc, char* argv[])
{
    func myfunc = add;
    printf("%d\n", add(1, 2));
    printf("%d\n", myfunc(3, 4));
    return 0;
}