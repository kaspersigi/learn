char* g_str = "Hello World! -- global\n";

int main(int argc, char* argv[])
{
    char* p_str = "Hello World! -- local\n";
    __asm__ __volatile__("\
        movl $4, %eax\n\t\
        movl $1, %ebx\n\t\
        movl g_str, %ecx\n\t\
        movl $24, %edx\n\t\
        int $0x80");
#if 0
    __asm__ __volatile__("\
        movl $4, %eax\n\t\
        movl $1, %ebx\n\t\
        movl %1, %ecx\n\t\
        movl $23, %edx\n\t\
        int $0x80"
                         :
                         : "c"(p_str));
#endif

    return 0;
}