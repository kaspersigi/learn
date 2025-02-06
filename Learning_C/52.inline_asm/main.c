#include <stdio.h>

typedef struct {
    int counter;
} atomic_t;

static inline void atomic_set(atomic_t* v, int i)
{
    v->counter = i;
}

static inline void atomic_add(int i, atomic_t* v)
{
    __asm__ __volatile__("addl %1, %0" // 汇编语句 %0 result, %1 data1, %2 data2
        : "+m"(v->counter) // 输出寄存器
        : "ir"(i)); // 输入寄存器
}

static inline void atomic_sub(int i, atomic_t* v)
{
    __asm__ __volatile__("subl %1, %0"
        : "+m"(v->counter)
        : "ir"(i));
}

static inline void atomic_inc(atomic_t* v)
{
    __asm__ __volatile__("incl %0"
        : "+m"(v->counter));
}

static inline int atomic_read(const atomic_t* v)
{
    return (*(__volatile__ int*)&(v)->counter);
}

int main(int argc, char* argv[])
{
    atomic_t count;
    atomic_set(&count, 0);
    printf("count = %d\n", atomic_read(&count));
    atomic_add(2, &count);
    printf("count = %d\n", atomic_read(&count));
    atomic_inc(&count);
    printf("count = %d\n", atomic_read(&count));
    atomic_sub(3, &count);
    printf("count = %d\n", atomic_read(&count));

    return 0;
}