#include "ftrace.h"
#include <unistd.h>

int main(int argc, char* argv[])
{
    int ret = 0;
    if (!ftrace_init())
        return -1;

    ftrace_duration_begin("MyFtrace");
    sleep(3);
    ftrace_duration_end();
    ftrace_close();

    return 0;
}