#define _POSIX_C_SOURCE 200809L

#include <android/log.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "LZZ_CTEST"

#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

char* g_buf1 = NULL;
char* g_buf2 = NULL;
char g_cmd[256] = { 0 };
const char* blank = "------------------------------\n";

void func1(int signum)
{
    LOGI("native_buf receive signal %d -- lzz", signum);
    system(g_cmd);
    printf("%s", blank);
    g_buf1 = (char*)malloc(4096);
    memset(g_buf1, 'A', 4096);
    system(g_cmd);
    printf("%s", blank);
}

void func2(int signum)
{
    LOGI("native_buf receive signal %d -- lzz", signum);
    system(g_cmd);
    printf("%s", blank);
    g_buf2 = (char*)malloc(8192);
    memset(g_buf2, 'B', 8192);
    system(g_cmd);
    printf("%s", blank);
}

int main(int argc, char* argv[])
{
    LOGI("native_buf start -- lzz");
    LOGI("native_buf pid = %d -- lzz", getpid());
    snprintf(g_cmd, sizeof(g_cmd), "cat /proc/%d/smaps_rollup", getpid());
    while (true) {
        signal(SIGUSR1, func1);
        signal(SIGUSR2, func2);
        pause();
    }
    printf("%s\n", g_buf1);
    printf("%s\n", g_buf2);
    free(g_buf1);
    free(g_buf2);
    g_buf1 = NULL;
    g_buf2 = NULL;
    LOGI("native_buf end -- lzz");

    return 0;
}