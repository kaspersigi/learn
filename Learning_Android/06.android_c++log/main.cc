#include <android/log.h>

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "LZZ_CPPTEST"

#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

auto main(int argc, char* argv[]) -> int
{
    for (size_t i = 0; i < 100; ++i)
        LOGI("Hello World! -- lzz");

    return 0;
}