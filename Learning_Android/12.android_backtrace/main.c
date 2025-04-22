#define _POSIX_C_SOURCE 200809L

#include "backtrace.h"
#include <signal.h>
#include <stdbool.h>
#include <sys/types.h>
#include <unistd.h>

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "LZZ_CTEST"

#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

void func(int signum)
{
    LOGI("backtrace receive signal %d", signum);
    LOGI("backtrace E");
    backtrace();
    LOGI("backtrace X");
    return;
}

int main(int argc, char* argv[])
{
    LOGI("backtrace start");
    LOGI("backtrace pid = %d", getpid());
    while (true) {
        signal(SIGUSR1, func);
        pause();
    }
    LOGI("backtrace end");

    return 0;
}