#include <CL/opencl.h>
#include <android/log.h>
#include <stdlib.h>

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "LZZ_CLTEST"

#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

static const size_t KNL_NUM = 1;

int main(int argc, char* argv[])
{
    cl_int err = CL_SUCCESS;
    cl_uint numPlatforms = 0;

    err = clGetPlatformIDs(0, NULL, &numPlatforms);

    if (err == CL_SUCCESS) {
        LOGI("%u platform(s) found", numPlatforms);
    } else {
        LOGE("clGetPlatformIDs(%i)", err);
        exit(-1);
    }

    cl_platform_id* PlatformIDs = (cl_platform_id*)calloc(numPlatforms, sizeof(cl_platform_id));
    err = clGetPlatformIDs(numPlatforms, PlatformIDs, NULL);

    for (cl_uint i = 0; i < numPlatforms; ++i) {
        cl_platform_id platformID = PlatformIDs[i];
        size_t size;
        err = clGetPlatformInfo(platformID, CL_PLATFORM_NAME, 0, NULL, &size);
        char* name = calloc(size + 1, sizeof(char));

        err = clGetPlatformInfo(platformID, CL_PLATFORM_NAME, size, name, NULL);
        LOGI("platformID name: %s", name);
        free(name);
        name = NULL;
    }

    cl_uint numCPUDevices = 0;
    cl_uint numGPUDevices = 0;
    err = clGetDeviceIDs(PlatformIDs[0], CL_DEVICE_TYPE_CPU, 0, NULL, &numCPUDevices);
    LOGI("platformIDs[0] %u cpu device(s) found", numCPUDevices);
    err = clGetDeviceIDs(PlatformIDs[0], CL_DEVICE_TYPE_GPU, 0, NULL, &numGPUDevices);
    LOGI("platformIDs[0] %u gpu device(s) found", numGPUDevices);

    free(PlatformIDs);
    PlatformIDs = NULL;

    return 0;
}