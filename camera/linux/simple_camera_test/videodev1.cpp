#include "videodev1.h"

//linux
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <iostream>
#include <string>

namespace linux_videodev  {

void GetDeviceNames(bool bVerbose, TDeviceNames& deviceNames)
{
    if (bVerbose) {
        std::cout << '[' << __PRETTY_FUNCTION__ <<  ':' << __LINE__ << ']' << ">>>" << std::endl;
    }

    uint32_t count = 0;
    char device[20] = {0};
    int fd = -1;

    /* detect /dev/video [0-63]VideoCaptureModule entries */
    for (int n = 0; n < 64; n++) {
        sprintf(device, "/dev/video%d", n);
        std::string nameDevice = device;
        if ((fd = open(device, O_RDONLY)) != -1) {
            close(fd);
            if (bVerbose) {
                std::cout << '[' << __PRETTY_FUNCTION__ <<  ':' << __LINE__ << ']'
                          << count << ":" << nameDevice << std::endl;
            }
            deviceNames.push_back(nameDevice);
            count++;
        } else {
            if (bVerbose) {
                std::cout << '[' << __PRETTY_FUNCTION__ <<  ':' << __LINE__ << ']'
                          << "open() failed:" << nameDevice <<std::endl;
            }
        }
    }

    if (bVerbose) {
        std::cout << '[' << __PRETTY_FUNCTION__ <<  ':' << __LINE__ << ']' << "<<<" << std::endl;
    }
}

} // namespace linux_videodev
