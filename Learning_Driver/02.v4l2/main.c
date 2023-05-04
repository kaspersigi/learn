#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <linux/videodev2.h>
#include <sys/ioctl.h>

int main(int argc, char* argv[])
{
    // 1、打开摄像头
    int fd = open("/dev/video0", O_RDWR);
    if (fd < 0) {
        perror("open");
        exit(-1);
    }

    // 2、获取功能参数
    struct v4l2_capability cap = {};
    int res = ioctl(fd, VIDIOC_QUERYCAP, &cap);
    if (res < 0) {
        perror("ioctl cap");
        exit(-1);
    }
    // 是一个摄像头
    if (cap.capabilities & V4L2_CAP_VIDEO_CAPTURE) {
        printf("This is a video capture device.\n");
        printf("driver: %s\n", cap.driver);
        printf("card: %s\n", cap.card);
        printf("bus_info: %s\n", cap.bus_info);
        printf("version: %x\n", cap.version);
        printf("capabilities: %x\n", cap.capabilities);
    } else {
        printf("This isn't a video capture device.\n");
        exit(-1);
    }

    // 3、获取摄像头支持的格式
    struct v4l2_fmtdesc fmt = {};
    fmt.index = 0; // 第一种格式
    fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE; // 获取摄像头的格式
    while (ioctl(fd, VIDIOC_ENUM_FMT, &fmt) == 0) {
        printf("pixelformat = %c%c%c%c, description = %s\n", fmt.pixelformat & 0xff, (fmt.pixelformat >> 8) & 0xff, (fmt.pixelformat >> 16) & 0xff, (fmt.pixelformat >> 24) & 0xff, fmt.description);
        ++fmt.index;
    }

    close(fd);
    return 0;
}