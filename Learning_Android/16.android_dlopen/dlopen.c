#include "ftrace.h"
#include <dlfcn.h>
#include <stdio.h>
#include <unistd.h>

typedef int (*FUNC)(int);

int main(int argc, char* argv[])
{
    int ret = 0;
    if (!ftrace_init())
        return -1;

    ret = ftrace_duration_begin("MainThread");

    void* handle = dlopen("./libfunc.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "dlopen failed: %s\n", dlerror());
    }
    sleep(1);
    FUNC func = (FUNC)dlsym(handle, "func");
    int result = func(1);
    printf("result = %d\n", result);
    sleep(1);
    dlclose(handle);

    ret = ftrace_duration_end();
    ftrace_close();

    return 0;
}