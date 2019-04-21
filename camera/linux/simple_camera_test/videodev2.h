#ifndef VIDEODEV2_H
#define VIDEODEV2_H

#include "test_types.h"

#include <string>

namespace linux_videodev2  {

void GetCapability(bool bVerbose, const std::string& sDeviceName, int fd);

}


#endif // VIDEODEV2_H
