#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static const int WRITE_OFFSET = 32;
static int g_trace_marker_fd = -1;
static pthread_mutex_t mutex;

void trace_begin(char* message)
{
    int length = strlen(message);
    char buf[length + WRITE_OFFSET];
    size_t len = sprintf(buf, "B|%d|%s", getpid(), message);
    pthread_mutex_trylock(&mutex);
    write(g_trace_marker_fd, buf, len);
    pthread_mutex_unlock(&mutex);
}

void trace_end()
{
    const char buf[2] = { 'E', '|' };
    pthread_mutex_trylock(&mutex);
    write(g_trace_marker_fd, buf, sizeof(buf));
    pthread_mutex_unlock(&mutex);
}

int main(int argc, char* argv[])
{
    if (g_trace_marker_fd == -1) {
        g_trace_marker_fd = open("/sys/kernel/tracing/trace_marker", O_WRONLY);
        if (g_trace_marker_fd == -1) {
            g_trace_marker_fd = open("/sys/kernel/debug/tracing/trace_marker", O_WRONLY);
        }
    }
    if (g_trace_marker_fd) {
        printf("open trace_market success!\n");
    } else {
        printf("open trace_market failed!\n");
        exit(-1);
    }

    trace_begin("MyFTrace");
    for (size_t i = 0; i < 500; ++i) {
        printf("Hello World!\n");
        usleep(10000);
    }
    trace_end();
    close(g_trace_marker_fd);
    usleep(10000);

    return 0;
}