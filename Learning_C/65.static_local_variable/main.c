#include <stdio.h>

void func()
{
    static int num = 0;
    printf("num = %d\n", num);
    ++num;
}

int main(int argc, char* argv[])
{
    func();
    func();
    func();
    printf("Hello World!");

    return 0;
}