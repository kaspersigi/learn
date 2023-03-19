void func()
{
    char* str = "Hello World! -- local\n";
    int ret = 0;

    // write() 4号系统调用
    __asm__ __volatile__("int $0x80"
                         : "=a"(ret)
                         : "a"(4), "b"(1), "c"(str), "d"(24));
}