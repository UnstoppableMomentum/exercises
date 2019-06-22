// Simple pattern to implement command line options
// no third party libraries required
// based on getopt()
// see http://man7.org/linux/man-pages/man3/getopt.3.html
//
// Command line options:
// t - test type, one of the following:
//     0: data races test
//     1: no data races test, implementation 1
//     2: no data races test, implementation 2
// n - number of test items, must be > 0
// s - number of threads, must be > 0

//Example:
// ./command_line -t 1 -n100 -s30
//OUTPUT:
// test type: 1
// number of test items: 100
// number of threads: 30

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <iostream>
#include <stdexcept>
#include <sstream>

const char kOptionTestType       [] = "test type";
const char kOptionNumOfTestItems [] = "number of test items";
const char kOptionNumberOfThreads[] = "number of threads";

// command line options
struct CmdLineOpt
{
    int iTestType = 0;
    int iDataSize = 100;
    int iThreadsCnt = 2;
};

void PrintHelp()
{
    CmdLineOpt opt;
    std::cout << "Command line options:" << std::endl
              << "t - " << kOptionTestType << ", on of the following:" << std::endl
              << "    0: data races test" << std::endl
              << "    1: no data races test (implementation 1)" << std::endl
              << "    2: no data races test (implementation 2)"
              << ", default value:" << opt.iTestType << std::endl
              << "n - " << kOptionNumOfTestItems << ", must be >0 and <3"
              << ", default value:" << opt.iDataSize << std::endl
              << "s - " << kOptionNumberOfThreads << ", must be >0"
              << ", default value:" << opt.iThreadsCnt << std::endl;
}

// parse integer command line parameter
bool ReadIntArg(int& iRes, const char* pArg) {
    bool bRes = false;
    if(pArg != nullptr) {
        char* pEnd = 0;
        iRes = static_cast<int>(strtol(pArg, &pEnd, 10));
        bRes = true;
    }
    return bRes;
}

int main (int argc, char **argv)
{
    CmdLineOpt cmdLineOpt;

    opterr = 0;
    bool bCmdLineOk = true;
    bool bHelp = false;
    std::stringstream ssErr;
    int opt = 0;
    while ((opt = getopt (argc, argv, "n:s:t:h")) != EOF) {
        switch (opt) {
        case '?':
            bHelp = true;
            break;
        case 'h':
            bHelp = true;
            break;
        case 't':
            bCmdLineOk = ReadIntArg(cmdLineOpt.iTestType, optarg);
            if (bCmdLineOk && ((cmdLineOpt.iTestType < 0) || (cmdLineOpt.iTestType > 2))) {
                ssErr << "parameter t:" << kOptionTestType << " is invalid.";
                bCmdLineOk = false;
            }
            break;
        case 'n':
            bCmdLineOk = ReadIntArg(cmdLineOpt.iDataSize, optarg);
            if (bCmdLineOk && (cmdLineOpt.iDataSize < 0)) {
                ssErr << "parameter n:" << kOptionNumOfTestItems << " is invalid.";
                bCmdLineOk = false;
            }
            break;
        case 's':
            bCmdLineOk = ReadIntArg(cmdLineOpt.iThreadsCnt, optarg);
            if (bCmdLineOk && (cmdLineOpt.iDataSize < 0)) {
                ssErr << "parameter n:" << kOptionNumberOfThreads << " is invalid.";
                bCmdLineOk = false;
            }
            break;
        }
        if (!bCmdLineOk) {
            break;
        }
    }

    if(!bCmdLineOk) {
        std::cout << ssErr.str() << std::endl;
    }

    if (!bCmdLineOk || bHelp) {
        PrintHelp();
    } else {
        std::cout
                << kOptionTestType        << ": " << cmdLineOpt.iTestType   << std::endl
                << kOptionNumOfTestItems  << ": " << cmdLineOpt.iDataSize   << std::endl
                << kOptionNumberOfThreads << ": " << cmdLineOpt.iThreadsCnt << std::endl;
    }
    return 0;
}
