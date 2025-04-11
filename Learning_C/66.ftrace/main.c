#include "ftrace.h"

int main(int argc, char* argv[])
{
    if (!trace_open()) {
        printf("%s: trace_open filed!\n", __PRETTY_FUNCTION__);
        return -1;
    }
    sleep(1);
    int ret = trace_dur_begin("MyFtrace");
    if (ret <= 0) {
        printf("%s: trace_dur_begin filed!\n", __PRETTY_FUNCTION__);
        return -1;
    }
    sleep(3);
    trace_dur_end();
    if (ret <= 0) {
        printf("%s: trace_dur_end filed!\n", __PRETTY_FUNCTION__);
        return -1;
    }
    trace_close();

    return 0;
}