char* g_str = "Hello World! -- global\n";

int main(int argc, char* argv[])
{
    char* p_str = "Hello World! -- local\n";
    int ret = 0;

    // write() 4号系统调用
    __asm__ __volatile__("int $0x80"
        : "=a"(ret)
        : "a"(4), "b"(1), "c"(g_str), "d"(24));

    // write() 4号系统调用
    __asm__ __volatile__("int $0x80"
        : "=a"(ret)
        : "a"(4), "b"(1), "c"(p_str), "d"(23));

    // exit() 1号系统调用
    __asm__ __volatile__("int $0x80"
        : "=a"(ret)
        : "a"(1), "b"(0));
}