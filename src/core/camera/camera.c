#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <linux/videodev2.h>
#include <sys/ioctl.h>

#define USB_CAMERA "/dev/video0"

void list_camera_formats(int fd)
{
    struct v4l2_fmtdesc fmt;
    struct v4l2_frmsizeenum frmsize;

    // 枚举支持的像素格式
    printf("支持的像素格式:\n");
    memset(&fmt, 0, sizeof(fmt));
    fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

    while (ioctl(fd, VIDIOC_ENUM_FMT, &fmt) == 0)
    {
        printf("  - 格式: %s (FourCC: %c%c%c%c)\n",
               fmt.description,
               fmt.pixelformat & 0xFF,
               (fmt.pixelformat >> 8) & 0xFF,
               (fmt.pixelformat >> 16) & 0xFF,
               (fmt.pixelformat >> 24) & 0xFF);

        // 获取此格式支持的分辨率
        memset(&frmsize, 0, sizeof(frmsize));
        frmsize.pixel_format = fmt.pixelformat;

        printf("    支持的分辨率:\n");
        while (ioctl(fd, VIDIOC_ENUM_FRAMESIZES, &frmsize) == 0)
        {
            if (frmsize.type == V4L2_FRMSIZE_TYPE_DISCRETE)
            {
                // 离散分辨率
                printf("      %ux%u\n", frmsize.discrete.width, frmsize.discrete.height);
            }
            else if (frmsize.type == V4L2_FRMSIZE_TYPE_STEPWISE)
            {
                // 连续分辨率范围
                printf("      %ux%u - %ux%u 步长: %ux%u\n",
                       frmsize.stepwise.min_width, frmsize.stepwise.min_height,
                       frmsize.stepwise.max_width, frmsize.stepwise.max_height,
                       frmsize.stepwise.step_width, frmsize.stepwise.step_height);
            }
            frmsize.index++;
        }

        fmt.index++;
    }

    if (errno != EINVAL)
    {
        perror("枚举像素格式失败");
    }
}

int main()
{
    // 打开设备
    int fd = open(USB_CAMERA, O_RDWR);
    if (fd < 0)
    {
        perror("打开摄像头失败");
        return -1;
    }

    // 列出摄像头支持的格式和分辨率
    list_camera_formats(fd);

    // 关闭设备
    close(fd);

    return 0;
}