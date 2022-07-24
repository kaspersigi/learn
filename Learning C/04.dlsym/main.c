#include <assert.h>
#include <dlfcn.h>
#include <stdio.h>

typedef int (*FUNC)(int);

int main(int argc, char* argv[])
{
    void* handle = dlopen("./libfunc.so", RTLD_LAZY);
    assert(handle);
    FUNC func = (FUNC)dlsym(handle, "func");
    int ret = func(1);
    printf("ret = %d\n", ret);
    return 0;
}