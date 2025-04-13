#include "ftrace.h"
#include <unistd.h>

int main(int argc, char* argv[])
{
    int ret = 0;
    if (!ftrace_init())
        return -1;

    ret = ftrace_duration_begin("MyFtrace");
    sleep(3);
    ret = ftrace_duration_end();
    ftrace_close();

    return 0;
}