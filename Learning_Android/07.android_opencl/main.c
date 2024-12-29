#include <CL/opencl.h>
#include <android/log.h>

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "LZZ_CLTEST"

#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

int main(int argc, char* argv[])
{
    cl_int CL_err = CL_SUCCESS;
    cl_uint numPlatforms = 0;

    CL_err = clGetPlatformIDs(0, NULL, &numPlatforms);

    if (CL_err == CL_SUCCESS)
        LOGI("%u platform(s) found", numPlatforms);
    else
        LOGE("clGetPlatformIDs(%i)", CL_err);

    return 0;
}