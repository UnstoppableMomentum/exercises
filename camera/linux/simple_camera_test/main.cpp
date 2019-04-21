#include <iostream>
#include <string>

#include <stdio.h>
#include <stdlib.h>

#include "tests.h"

void ReadArg(std::string& sVal, const std::string& sOption, const std::string& sKey)
{
    std::string sArg(sKey);
    sArg += ":";

    // different member versions of find in the same order as above:
    std::size_t found = sOption.find(sArg);
    if ((found!=std::string::npos) && (sOption.length() > sArg.length())) {
        sVal = sOption.substr(sArg.length(), sOption.length() -1);
    }
}

int main(int argc, char *argv[])
{
    bool bHelp = argc < 2;
    bool bVerbose = false;
    bool bTestGetDeviceNames = false;
    bool bTestOpenclose = false;
    bool bGetCapability2 = false;
    bool bGetCapability = false;

    std::string sTask;
    std::string sDevice;
    std::string sFormat;

    for (int arg = 1; arg < argc; ++arg) {
        std::string option = argv[arg];
        if (("-h" == option) || ("-help" == option) || ("--help" == option))  {
            bHelp = true;
        }

        if (('-' == option[0]) && (option.length() > 1)) {
            sTask = option.substr(1, option.length() -1);
        } else {
            ReadArg(sDevice, option, kDeviceName);
            ReadArg(sFormat, option, kFormat);
        }

        if (kOptionVerbose == sTask) {
            bVerbose = true;
        }

        if (kOptionDeviceNames == sTask) {
            bTestGetDeviceNames = true;
        }

        if (kOptionOpenClose == sTask) {
            bTestOpenclose = true;
        }

        if (kGetCapability2 == sTask) {
            bGetCapability2 = true;
        }

        if (kGetCapability == sTask) {
            bGetCapability = true;
        }


    }

    bHelp = (!bTestOpenclose)
            && (!bTestGetDeviceNames)
            && (!bGetCapability)
            && (!bGetCapability2);

    if (bVerbose) {
        for (int arg = 0; arg < argc; ++arg) {
            std::cout << "arg:" << arg << " value:" << argv[arg] << std::endl;
        }
    }

    if(bHelp) {
        PrintHelp();
    } else {

        if (bTestGetDeviceNames) {
            TestGetDeviceNames(bVerbose);
        }

        if (bTestOpenclose) {
            if(sDevice.empty()) {
                TestOpenCloseDevices(bVerbose);
            } else {
                TestOpenCloseDevice(bVerbose, sDevice);
            }
        }

        if (bGetCapability) {            
            //TestCapabilities(bVerbose);
        }

        if (bGetCapability2) {
            if(sDevice.empty()) {
                TestCapabilities2(bVerbose);
            } else {
                TestCapability2(bVerbose, sDevice);
            }
        }
    }
    return 0;
}
