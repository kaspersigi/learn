#include <dlfcn.h>
#include <stdio.h>

typedef int (*FUNC)(int);

int main(int argc, char* argv[])
{
    void* handle = dlopen("./libfunc.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "dlopen failed: %s\n", dlerror());
    }
    FUNC func = (FUNC)dlsym(handle, "func");
    int ret = func(1);
    printf("ret = %d\n", ret);
    dlclose(handle);

    return 0;
}