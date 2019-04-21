#ifndef VIDEODEV1_H
#define VIDEODEV1_H


#include "test_types.h"

#include <string>

namespace linux_videodev  {

void GetDeviceNames(bool bVerbose, TDeviceNames& deviceNames);

} // namespace linux_videodev

#endif // VIDEODEV1_H
