#pragma once

#include <fcntl.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static const int WRITE_OFFSET = 32;
static int g_trace_marker_fd = -1;
static pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;

bool trace_open()
{
    if (g_trace_marker_fd <= 0) {
        g_trace_marker_fd = open("/sys/kernel/tracing/trace_marker", O_WRONLY);
    }
    if (g_trace_marker_fd > 0) {
        printf("%s: open trace_marker success!\n", __PRETTY_FUNCTION__);
        return true;
    } else {
        printf("%s: open trace_marker failed!\n", __PRETTY_FUNCTION__);
        g_trace_marker_fd = -1;
        return false;
    }
}

void trace_close()
{
    close(g_trace_marker_fd);
    g_trace_marker_fd = -1;
    printf("%s: close trace_marker success!\n", __PRETTY_FUNCTION__);
}

int trace_dur_begin(const char* message)
{
    int length = strlen(message);
    char buf[length + WRITE_OFFSET];
    size_t len = sprintf(buf, "B|%d|%s", getpid(), message);
    pthread_mutex_lock(&g_mutex);
    int ret = write(g_trace_marker_fd, buf, len);
    pthread_mutex_unlock(&g_mutex);
    printf("%s: write %d bytes!\n", __PRETTY_FUNCTION__, ret);
    return ret;
}

int trace_dur_end()
{
    char buf[WRITE_OFFSET];
    size_t len = sprintf(buf, "E|%d", getpid());
    pthread_mutex_lock(&g_mutex);
    int ret = write(g_trace_marker_fd, buf, len);
    pthread_mutex_unlock(&g_mutex);
    printf("%s: write %d bytes!\n", __PRETTY_FUNCTION__, ret);
    return ret;
}