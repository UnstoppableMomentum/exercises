#include "tests.h"

//linux
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <iostream>
#include <string>

void PrintHelp()
{
    std::cout << " Command line options:" << std::endl
              << "-" << kOptionVerbose << ": verbose mode" << std::endl
              << "-" << kOptionDeviceNames << ": list device names" << std::endl
              << "-" << kOptionOpenClose << ": open - close all the available video devices" << std::endl
              << "-" << kGetCapability << ": get video devices capabilities" << std::endl
              << "-" << kGetCapability2 << ": get video devices capabilities ver 2" << std::endl
              << kDeviceName << ":" << "devicename" << std::endl
              << kFormat << ":" << "format" << std::endl;
}

void TestGetDeviceNames(bool bVerbose)
{
    if(bVerbose) {
        std::cout << '[' << __PRETTY_FUNCTION__ <<  ':' << __LINE__ << ']' << ">>>" << std::endl;
    }
    TDeviceNames deviceNames;
    linux_videodev::GetDeviceNames(bVerbose, deviceNames);
    for(TDeviceNames::const_iterator it(deviceNames.begin()); it != deviceNames.end(); ++it) {
        std::cout << *it << std::endl;
    }
    if(bVerbose) {
        std::cout << '[' << __PRETTY_FUNCTION__ <<  ':' << __LINE__ << ']' << "<<<" << std::endl;
    }
}

void TestOpenCloseDevice(bool bVerbose, const std::string& sDeviceName)
{
    if(bVerbose) {
        std::cout << '[' << __PRETTY_FUNCTION__ <<  ':' << __LINE__ << ']' << ">>>" << std::endl;
    }

    std::cout << sDeviceName;
    int fd =  open(sDeviceName.c_str(), O_RDWR);
    if (fd == -1) {
        std::cout << " ERR: open():" << fd << std::endl;
    } else {
        std::cout << " open():" << fd << std::endl;
        int res = close(fd);
        if(0 == res) {
            std::cout << " close():" << res << std::endl;
        } else {
            std::cout << "ERR: close():" << res << std::endl;
        }
    }

    if(bVerbose) {
        std::cout << '[' << __PRETTY_FUNCTION__ <<  ':' << __LINE__ << ']' << "<<<" << std::endl;
    }
}

void TestOpenCloseDevices(bool bVerbose)
{
    std::cout << '[' << __PRETTY_FUNCTION__ <<  ':' << __LINE__ << ']' << ">>>" << std::endl;
    TDeviceNames deviceNames;
    linux_videodev::GetDeviceNames(false, deviceNames);
    for(TDeviceNames::const_iterator it(deviceNames.begin()); it != deviceNames.end(); ++it) {
        TestOpenCloseDevice(bVerbose, *it);
    }
    std::cout << '[' << __PRETTY_FUNCTION__ <<  ':' << __LINE__ << ']' << "<<<" << std::endl;
}

void TestCapabilities(bool /*bVerbose*/, const std::string& sDeviceName)
{
    std::cout << '[' << __PRETTY_FUNCTION__ <<  ':' << __LINE__ << ']' << ">>>" << std::endl;
    std::cout << '[' << __PRETTY_FUNCTION__ <<  ':' << __LINE__ << ']' << "<<<" << std::endl;
}

void TestCapability2(bool bVerbose, const std::string& sDeviceName)
{
    if(bVerbose) {
        std::cout << '[' << __PRETTY_FUNCTION__ <<  ':' << __LINE__ << ']' << ">>>" << std::endl;
    }
    std::cout << sDeviceName;
    int fd =  open(sDeviceName.c_str(), O_RDWR);
    if (fd == -1) {
        std::cout << " ERR: open():" << fd << std::endl;
    } else {
        std::cout << " open():" << fd << std::endl;
        linux_videodev2::GetCapability(bVerbose, sDeviceName, fd);
        int res = close(fd);
        if(0 == res) {
            std::cout << " close():" << res << std::endl;
        } else {
            std::cout << "ERR: close():" << res << std::endl;
        }
    }
    if(bVerbose) {
        std::cout << '[' << __PRETTY_FUNCTION__ <<  ':' << __LINE__ << ']' << "<<<" << std::endl;
    }
}

void TestCapabilities2(bool bVerbose)
{
    if(bVerbose) {
        std::cout << '[' << __PRETTY_FUNCTION__ <<  ':' << __LINE__ << ']' << ">>>" << std::endl;
    }
    TDeviceNames deviceNames;
    linux_videodev::GetDeviceNames(false, deviceNames);
    for(TDeviceNames::const_iterator it(deviceNames.begin()); it != deviceNames.end(); ++it) {
        TestCapability2(bVerbose, *it);
    }
    if(bVerbose) {
        std::cout << '[' << __PRETTY_FUNCTION__ <<  ':' << __LINE__ << ']' << "<<<" << std::endl;
    }
}
