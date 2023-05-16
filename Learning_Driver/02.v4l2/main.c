#include <fcntl.h>
#include <linux/videodev2.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>

const char dev[] = "/dev/video0";
const size_t buf_count = 4;

// 用户层缓冲区保存结构体
typedef struct buf_type {
    void* start;
    int length;
} buf_type;

/**
 * @brief init_camera 初始化相机设备属性
 * @param dev 设备名称
 * @return 成功返回fd, 失败返回-1
 */
int init_camera(const char* dev);

/**
 * @brief mmap_buffer 分配用户缓冲区内存，并建立内存映射
 * @param fd 设备描述符
 * @return 成功返回usr_buf，失败返回-1
 */
buf_type* mmap_buffer(int fd);

/**
 * @brief stream_on 开启视频流
 * @param fd 设备描述符
 * @param usr_buf 用户空间缓存
 * @return 成功返回0，失败返回-1
 */
int stream_on(int fd);

/**
 * @brief write_frame 读取一帧图像
 * @param fd 设备描述符
 * @param usr_buf 用户空间缓存
 * @return 返回图像帧的索引index，读取失败返回-1
 */
int write_frame(int fd, buf_type* usr_buf);

/**
 * @brief stream_off 关闭视频流
 * @param fd 设备描述符
 * @return 成功返回0，失败返回-1
 */
int stream_off(int fd);

/**
 * @brief unmap_buffer 解除缓冲区映射
 * @param usr_buf 用户空间缓存
 * @return 成功返回0，失败返回-1
 */
int unmap_buffer(buf_type* usr_buf);

/**
 * @brief release_camera 关闭设备
 * @param fd 设备描述符
 */
void release_camera(int fd);

int main(int argc, char* argv[])
{
    int ret = -1;
    int fd = init_camera(dev);
    if (fd < 0) {
        perror("init_camera");
        exit(-1);
    }

    buf_type* usr_buf = mmap_buffer(fd);
    if (usr_buf < 0) {
        perror("mmap_buffer");
        exit(-1);
    }

    ret = stream_on(fd);
    if (ret < 0) {
        perror("stream_on");
        exit(-1);
    }

    for (size_t i = 0; i < 4; ++i) {
        write_frame(fd, usr_buf);
    }

    ret = stream_off(fd);
    if (ret < 0) {
        perror("stream_off");
        exit(-1);
    }

    ret = unmap_buffer(usr_buf);
    if (ret < 0) {
        perror("unmap_buffer");
        exit(-1);
    }

    release_camera(fd);
    return 0;
}

int init_camera(const char* dev)
{
    // 打开摄像头
    int fd = open(dev, O_RDWR);
    if (fd < 0) {
        perror("open");
        exit(-1);
    }

    // 查询设备属性
    struct v4l2_capability cap;
    int ret = ioctl(fd, VIDIOC_QUERYCAP, &cap);
    if (ret < 0) {
        perror("VIDIOC_QUERYCAP");
        exit(-1);
    }

    printf("driver: %s\n", cap.driver);
    printf("card: %s\n", cap.card);
    printf("bus_info: %s\n", cap.bus_info);
    printf("version: %x\n", cap.version);
    printf("capabilities: %x\n", cap.capabilities);

    // 判断是否为视频捕获设备
    if (cap.capabilities & V4L2_BUF_TYPE_VIDEO_CAPTURE) {
        // 判断是否支持视频流捕获
        if (cap.capabilities & V4L2_CAP_STREAMING) {
            printf("support stream capture\n");
        }
        else {
            printf("unsupport stream capture\n");
        }
    }
    else {
        perror("VIDEO_CAPTURE");
        exit(-1);
    }

    struct v4l2_fmtdesc fmtdesc;
    fmtdesc.index = 0;
    fmtdesc.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    printf("supported video format:\n");
    while (ioctl(fd, VIDIOC_ENUM_FMT, &fmtdesc) == 0) {
        printf("\t%d.%s\n", fmtdesc.index + 1, fmtdesc.description);
        fmtdesc.index++;
    }

    // 设置摄像头采集通道
    int index = 0; // 第一个通道
    if (ioctl(fd, VIDIOC_S_INPUT, &index) < 0) {
        perror("VIDIOC_S_INPUT");
        exit(-1);
    }

    // 设置格式
    struct v4l2_format fmt;
    fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    fmt.fmt.pix.width = 640;
    fmt.fmt.pix.height = 480;
    fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;
    if (ioctl(fd, VIDIOC_S_FMT, &fmt) < 0) {
        perror("set foramt: V4L2_PIX_FMT_YUYV");
        exit(-1);
    }

    return fd;
}

buf_type* mmap_buffer(int fd)
{
    // 申请用户缓存空间
    buf_type* usr_buf = calloc(buf_count, sizeof(buf_type));
    if (!usr_buf) {
        perror("calloc \"frame buffer\" : Out of memory");
        exit(-1);
    }

    // 申请内核缓存空间
    struct v4l2_requestbuffers req;
    req.count = buf_count; // 帧缓冲数量
    req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE; // 视频捕获缓冲区类型
    req.memory = V4L2_MEMORY_MMAP; // 内存映射方式
    if (ioctl(fd, VIDIOC_REQBUFS, &req) < 0) {
        perror("VIDIOC_REQBUFS");
        exit(-1);
    }

    // 映射内核缓存区到用户空间缓冲区
    for (size_t i = 0; i < buf_count; ++i) {
        // 查询内核缓冲区信息
        struct v4l2_buffer v4l2_buf;
        memset(&v4l2_buf, 0, sizeof(v4l2_buf));
        v4l2_buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        v4l2_buf.memory = V4L2_MEMORY_MMAP;
        v4l2_buf.index = i;
        if (ioctl(fd, VIDIOC_QUERYBUF, &v4l2_buf) < 0) {
            perror("VIDIOC_QUERYBUF");
            exit(-1);
        }

        /* 建立映射关系
         * 注意这里的索引号，v4l2_buf.index 与 usr_buf 的索引是一一对应的,
         * 当我们将内核缓冲区出队时，可以通过查询内核缓冲区的索引来获取用户缓冲区的索引号，
         * 进而能够知道应该在第几个用户缓冲区中取数据
         */
        usr_buf[i].length = v4l2_buf.length;
        usr_buf[i].start = (char*)mmap(0, v4l2_buf.length, PROT_READ | PROT_WRITE, MAP_SHARED, fd, v4l2_buf.m.offset);

        // 若映射失败,打印错误
        if (MAP_FAILED == usr_buf[i].start) {
            printf("mmap failed: %lu\n", i);
            exit(-1);
        }
        else {
            // 若映射成功则将内核缓冲区入队
            if (ioctl(fd, VIDIOC_QBUF, &v4l2_buf) < 0) {
                perror("VIDIOC_QBUF");
                exit(-1);
            }
        }
    }
    return usr_buf;
}

int stream_on(int fd)
{
    enum v4l2_buf_type type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if (ioctl(fd, VIDIOC_STREAMON, &type) < 0) {
        perror("VIDIOC_STREAMON");
        exit(-1);
    }
    return 0;
}

int write_frame(int fd, buf_type* usr_buf)
{
    struct v4l2_buffer v4l2_buf;
    v4l2_buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    v4l2_buf.memory = V4L2_MEMORY_MMAP;
    // 内核缓冲区出队列
    if (ioctl(fd, VIDIOC_DQBUF, &v4l2_buf) < 0) {
        perror("VIDIOC_DQBUF");
        exit(-1);
    }

    // 因为内核缓冲区与用户缓冲区建立的映射，所以可以通过用户空间缓冲区直接访问这个缓冲区的数据
    char buffer[256] = {};
    sprintf(buffer, "./%d.yuyv", v4l2_buf.index);
    int file_fd = open(buffer, O_RDWR | O_CREAT); // 若打开失败则不存储该帧图像
    memset(buffer, 0, 256);
    if (file_fd < 0) {
        perror("open file");
        exit(-1);
    }
    else {
        write(file_fd, usr_buf[v4l2_buf.index].start, v4l2_buf.bytesused);
        close(file_fd);
        printf("saving %d images\n", v4l2_buf.index);
    }

    // 缓冲区重新入队
    if (ioctl(fd, VIDIOC_QBUF, &v4l2_buf) < 0) {
        perror("VIDIOC_QBUF again");
        exit(-1);
    }
    return v4l2_buf.index;
}

int stream_off(int fd)
{
    // 关闭视频流
    enum v4l2_buf_type type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if (ioctl(fd, VIDIOC_STREAMOFF, &type) < 0) {
        perror("VIDIOC_STREAMOFF");
        exit(-1);
    }
    return 0;
}

int unmap_buffer(buf_type* usr_buf)
{
    // 解除内核缓冲区到用户缓冲区的映射
    for (unsigned int i = 0; i < buf_count; i++) {
        int ret = munmap(usr_buf[i].start, usr_buf[i].length);
        if (ret < 0) {
            printf("munmap failed\n");
            return -1;
        }
    }
    free(usr_buf); // 释放用户缓冲区内存
    return 0;
}

void release_camera(int fd)
{
    close(fd);
}