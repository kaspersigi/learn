#include "ftrace.h"
#include <CL/cl.h>
#include <stdio.h>
#include <stdlib.h>

#define DATA_SIZE 10

void printDeviceInfo(cl_device_id device)
{
    int ret = 0;
    char device_name[128];
    char vendor_name[128];

    ret = ftrace_duration_begin("clGetDeviceInfo");
    clGetDeviceInfo(device, CL_DEVICE_NAME, sizeof(device_name), device_name, NULL);
    ret = ftrace_duration_end();

    ret = ftrace_duration_begin("clGetDeviceInfo");
    clGetDeviceInfo(device, CL_DEVICE_VENDOR, sizeof(vendor_name), vendor_name, NULL);
    ret = ftrace_duration_end();

    printf("Device: %s, Vendor: %s\n", device_name, vendor_name);
}

int my_cl_program()
{
    int ret = 0;

    cl_int err;
    cl_platform_id platform;
    cl_device_id device;
    cl_context context;
    cl_command_queue queue;
    cl_program program;
    cl_kernel kernel;
    cl_mem a_mem, b_mem, result_mem;

    // 输入数据和输出数据
    float a[DATA_SIZE], b[DATA_SIZE], results[DATA_SIZE];
    for (int i = 0; i < DATA_SIZE; i++) {
        a[i] = (float)i;
        b[i] = (float)(DATA_SIZE - i);
    }

    // 1. 获取平台和设备
    ret = ftrace_duration_begin("clGetPlatformIDs");
    err = clGetPlatformIDs(1, &platform, NULL);
    ret = ftrace_duration_end();

    ret = ftrace_duration_begin("clGetDeviceIDs");
    err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, NULL);
    ret = ftrace_duration_end();

    printDeviceInfo(device);

    // 2. 创建OpenCL上下文和命令队列
    ret = ftrace_duration_begin("clCreateContext");
    context = clCreateContext(NULL, 1, &device, NULL, NULL, &err);
    ret = ftrace_duration_end();

    // 使用新的API创建命令队列
    cl_queue_properties properties[] = { CL_QUEUE_PROPERTIES, 0, 0 };
    ret = ftrace_duration_begin("clCreateCommandQueueWithProperties");
    queue = clCreateCommandQueueWithProperties(context, device, properties, &err);
    ret = ftrace_duration_end();

    // 3. 创建内存缓冲区
    ret = ftrace_duration_begin("clCreateBuffer");
    a_mem = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
        sizeof(float) * DATA_SIZE, a, &err);
    ret = ftrace_duration_end();

    ret = ftrace_duration_begin("clCreateBuffer");
    b_mem = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
        sizeof(float) * DATA_SIZE, b, &err);
    ret = ftrace_duration_end();

    ret = ftrace_duration_begin("clCreateBuffer");
    result_mem = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
        sizeof(float) * DATA_SIZE, NULL, &err);
    ret = ftrace_duration_end();

    // 4. 创建内核程序
    const char* kernel_source = "__kernel void vector_add(__global const float *a, __global const float *b, __global float *result) { \n"
                                "    int i = get_global_id(0); \n"
                                "    result[i] = a[i] + b[i]; \n"
                                "} \n";

    ret = ftrace_duration_begin("clCreateProgramWithSource");
    program = clCreateProgramWithSource(context, 1, &kernel_source, NULL, &err);
    ret = ftrace_duration_end();

    ret = ftrace_duration_begin("clBuildProgram");
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    ret = ftrace_duration_end();

    if (err != CL_SUCCESS) {
        char build_log[4096];

        ret = ftrace_duration_begin("clGetProgramBuildInfo");
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG,
            sizeof(build_log), build_log, NULL);
        ret = ftrace_duration_end();

        printf("Build error:\n%s\n", build_log);
        return -1;
    }

    // 5. 创建内核
    ret = ftrace_duration_begin("clCreateKernel");
    kernel = clCreateKernel(program, "vector_add", &err);
    ret = ftrace_duration_end();

    // 6. 设置内核参数
    ret = ftrace_duration_begin("clSetKernelArg");
    err = clSetKernelArg(kernel, 0, sizeof(cl_mem), &a_mem);
    ret = ftrace_duration_end();

    ret = ftrace_duration_begin("clSetKernelArg");
    err = clSetKernelArg(kernel, 1, sizeof(cl_mem), &b_mem);
    ret = ftrace_duration_end();

    ret = ftrace_duration_begin("clSetKernelArg");
    err = clSetKernelArg(kernel, 2, sizeof(cl_mem), &result_mem);
    ret = ftrace_duration_end();

    // 7. 执行内核
    size_t global_size = DATA_SIZE;
    ret = ftrace_duration_begin("clEnqueueNDRangeKernel");
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &global_size, NULL, 0, NULL, NULL);
    ret = ftrace_duration_end();

    // 8. 读取结果
    ret = ftrace_duration_begin("clEnqueueReadBuffer");
    err = clEnqueueReadBuffer(queue, result_mem, CL_TRUE, 0,
        sizeof(float) * DATA_SIZE, results, 0, NULL, NULL);
    ret = ftrace_duration_end();

    // 打印结果
    printf("Results:\n");
    for (int i = 0; i < DATA_SIZE; i++) {
        printf("%.2f + %.2f = %.2f\n", a[i], b[i], results[i]);
    }

    // 9. 清理资源
    ret = ftrace_duration_begin("clReleaseMemObject");
    clReleaseMemObject(a_mem);
    ret = ftrace_duration_end();

    ret = ftrace_duration_begin("clReleaseMemObject");
    clReleaseMemObject(b_mem);
    ret = ftrace_duration_end();

    ret = ftrace_duration_begin("clReleaseMemObject");
    clReleaseMemObject(result_mem);
    ret = ftrace_duration_end();

    ret = ftrace_duration_begin("clReleaseKernel");
    clReleaseKernel(kernel);
    ret = ftrace_duration_end();

    ret = ftrace_duration_begin("clReleaseProgram");
    clReleaseProgram(program);
    ret = ftrace_duration_end();

    ret = ftrace_duration_begin("clReleaseCommandQueue");
    clReleaseCommandQueue(queue);
    ret = ftrace_duration_end();

    ret = ftrace_duration_begin("clReleaseContext");
    clReleaseContext(context);
    ret = ftrace_duration_end();

    return 0;
}

int main(void)
{
    int ret = 0;
    if (!ftrace_init())
        return -1;

    ret = ftrace_duration_begin("MainThread");
    ret = my_cl_program();
    ret = ftrace_duration_end();

    ftrace_close();

    return 0;
}