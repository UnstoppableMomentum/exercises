#ifndef TESTS_H
#define TESTS_H

#include <string>

#include "videodev1.h"
#include "videodev2.h"



void PrintHelp();

void TestGetDeviceNames(bool bVerbose);

void TestOpenCloseDevices(bool bVerbose);
void TestOpenCloseDevice(bool bVerbose, const std::string& sDeviceName);

void TestCapabilities(bool bVerbose, const std::string& sDeviceName);

void TestCapability2(bool bVerbose, const std::string& sDeviceName);
void TestCapabilities2(bool bVerbose);

#endif // TESTS_H
