#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static const int WRITE_OFFSET = 32;
static int g_trace_marker_fd = -1;

void trace_begin(char* message)
{
    int length = strlen(message);
    char buf[length + WRITE_OFFSET];
    size_t len = sprintf(buf, "B|%d|%s", getpid(), message);
    write(g_trace_marker_fd, buf, len);
}

void trace_end()
{
    const char buf[2] = { 'E', '|' };
    write(g_trace_marker_fd, buf, sizeof(buf));
}

int main(int argc, char* argv[])
{
    if (g_trace_marker_fd == -1) {
        g_trace_marker_fd = open("/sys/kernel/tracing/trace_marker", O_WRONLY);
        if (g_trace_marker_fd == -1) {
            g_trace_marker_fd = open("/sys/kernel/debug/tracing/trace_marker", O_WRONLY);
        }
    }
    if (g_trace_marker_fd)
        printf("open trace_market success!\n");
    else
        printf("open trace_market failed!\n");

    trace_begin("MyFTrace");
    for (size_t i = 0; i < 500; ++i) {
        printf("Hello World!\n");
        usleep(10000);
    }
    trace_end();

    close(g_trace_marker_fd);
    return 0;
}