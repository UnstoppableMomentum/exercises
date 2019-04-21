#include "videodev2.h"

//linux
#include <errno.h>
#include <fcntl.h>
#include <linux/videodev2.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>

#include <iostream>
#include <string>

namespace linux_videodev2  {

static int xioctl(int fd, int request, void *arg)
{
    int r;

    do r = ioctl (fd, request, arg);
    while (-1 == r && EINTR == errno);

    return r;
}

void GetCapability(bool /*bVerbose*/, const std::string& sDeviceName, int fd)
{
    std::cout << '[' << __PRETTY_FUNCTION__ <<  ':' << __LINE__ << ']' << ">>>" << std::endl;

    struct v4l2_capability caps = {};
    if (-1 == xioctl(fd, VIDIOC_QUERYCAP, &caps)) {
        std::cout << '[' << __PRETTY_FUNCTION__ <<  ':' << __LINE__ << ']'
                  << " sDeviceName:" << sDeviceName
                  << " fd:" << fd
                  << std::endl;

    }

    int verMaj = (caps.version>>16) && 0xff;
    int verMin = (caps.version>>24) && 0xff;

    std::cout << " sDeviceName:" << sDeviceName
              << " fd:" << fd << std::endl
              << " Driver:" <<  caps.driver << std::endl
              << " Card:" << caps.card << std::endl
              << " Bus:" <<  caps.bus_info << std::endl
              << " Version:"<< verMaj << "." << verMin << std::endl
              << " Capabilities:" << std::hex << "0x"<< caps.capabilities  << std::endl
              << "    V4L2_CAP_VIDEO_CAPTURE:" << (caps.capabilities & V4L2_CAP_VIDEO_CAPTURE) << std::endl
              << "    V4L2_CAP_VIDEO_CAPTURE_MPLANE:" << (caps.capabilities & V4L2_CAP_VIDEO_CAPTURE_MPLANE) << std::endl
              << "    V4L2_CAP_VIDEO_OUTPUT:" << (caps.capabilities & V4L2_CAP_VIDEO_OUTPUT) << std::endl
              << "    V4L2_CAP_VIDEO_OUTPUT_MPLANE:" << (caps.capabilities & V4L2_CAP_VIDEO_OUTPUT_MPLANE) << std::endl
              << std::endl;

    struct v4l2_cropcap cropcap = {0};
    cropcap.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if (-1 == xioctl (fd, VIDIOC_CROPCAP, &cropcap))
    {
        std::cout << '[' << __PRETTY_FUNCTION__ <<  ':' << __LINE__ << ']'
                  << " sDeviceName:" << sDeviceName
                  << " fd:" << fd
                  << std::endl;
    }

    std::cout << "Camera Cropping" << std::endl
              << "  Bounds:"
              << std::dec
              << "    w:" << cropcap.bounds.width
              << "    h:" << cropcap.bounds.height
              << "    l:" << cropcap.bounds.left
              << "    t:" << cropcap.bounds.top << std::endl
              << " Default:"
              << "    w:" << cropcap.defrect.width
              << "    h:" << cropcap.defrect.height
              << "    l:" << cropcap.defrect.left
              << "    t:" << cropcap.defrect.top << std::endl
              << "  Aspect:"
              << cropcap.pixelaspect.numerator
              << "/" << cropcap.pixelaspect.denominator
              << std::endl;


    {
        std::cout << "V4L2_BUF_TYPE_VIDEO_CAPTURE >>>" << std::endl;
        struct v4l2_fmtdesc fmtdesc = {0};
        fmtdesc.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        char fourcc[5] = {0};
        char c, e;
        while (0 == xioctl(fd, VIDIOC_ENUM_FMT, &fmtdesc))
        {
            strncpy(fourcc, (char *)&fmtdesc.pixelformat, 4);
            c = fmtdesc.flags & 1? 'C' : ' ';
            e = fmtdesc.flags & 2? 'E' : ' ';
            std::cout << fourcc << ":" << c << e << " " << fmtdesc.description
                      << std::endl;
            fmtdesc.index++;
        }
        std::cout << "V4L2_BUF_TYPE_VIDEO_CAPTURE <<<" << std::endl;
    }

    {
        std::cout << "V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE >>>" << std::endl;
        struct v4l2_fmtdesc fmtdesc = {0};
        fmtdesc.type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
        char fourcc[5] = {0};
        char c, e;
        while (0 == xioctl(fd, VIDIOC_ENUM_FMT, &fmtdesc))
        {
            strncpy(fourcc, (char *)&fmtdesc.pixelformat, 4);
            c = fmtdesc.flags & 1? 'C' : ' ';
            e = fmtdesc.flags & 2? 'E' : ' ';
            std::cout << fourcc << ":" << c << e << " " << fmtdesc.description
                      << std::endl;
            fmtdesc.index++;
        }
        std::cout << "V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE <<<" << std::endl;
    }


    std::cout << '[' << __PRETTY_FUNCTION__ <<  ':' << __LINE__ << ']' << "<<<" << std::endl;
}

} //namespace linux_videodev2



