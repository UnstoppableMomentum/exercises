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
//
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

#include "cmd_line.h"
#include "test1.h"

// parse integer command line parameter
// TODO check T is integral type
template <typename T>
bool ReadIntArg(T& iRes, const char* pArg) {
    bool bRes = false;
    if(pArg != nullptr) {
        char* pEnd = 0;
        iRes = static_cast<T>(strtol(pArg, &pEnd, 10));
        bRes = true;
    }
    return bRes;
}

// command line options descripttion
const char kOptionTestType       [] = "test type";
const char kOptionNumOfTestItems [] = "number of test items";
const char kOptionNumberOfThreads[] = "number of threads";

void PrintHelp()
{
    TestOptions opt;
    std::cout << "Command line options:" << std::endl
              << "t - " << kOptionTestType << ", on of the following:" << std::endl
              << "    0: data races test" << std::endl
              << "    1: no data races test (implementation 1)" << std::endl
              << "    2: no data races test (implementation 2)"
              << ", default value:" << opt.eTestType << std::endl
              << "n - " << kOptionNumOfTestItems << ", must be >0 and <3"
              << ", default value:" << opt.iDataSize << std::endl
              << "s - " << kOptionNumberOfThreads << ", must be >0"
              << ", default value:" << opt.iThreadsCnt << std::endl;
}

bool parseCommandLine(TestOptions& options, bool bPrintArgs, int argc, char **argv)
{
    bool bRes = true;

    // getopt.h
    // Callers store zero here to inhibit the error message `getopt' prints
    // for unrecognized options.
    // extern int opterr;
    opterr = 0;

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
            bRes = ReadIntArg(options.eTestType, optarg);
            if (bRes && ((options.eTestType < 0) || (options.eTestType > 2))) {
                ssErr << "parameter t:" << kOptionTestType << " is invalid.";
                bRes = false;
            }
            break;
        case 'n':
            bRes = ReadIntArg(options.iDataSize, optarg);
            if (bRes && (options.iDataSize < 0)) {
                ssErr << "parameter n:" << kOptionNumOfTestItems << " is invalid.";
                bRes = false;
            }
            break;
        case 's':
            bRes = ReadIntArg(options.iThreadsCnt, optarg);
            if (bRes && (options.iDataSize < 0)) {
                ssErr << "parameter n:" << kOptionNumberOfThreads << " is invalid.";
                bRes = false;
            }
            break;
        }
        if (!bRes) {
            break;
        }
    }

    if(!bRes) {
        std::cout << ssErr.str() << std::endl;
    }

    if (!bRes || bHelp) {
        PrintHelp();
        bRes = false;
    } else {
        if (bPrintArgs) {
            std::cout
                    << kOptionTestType        << ": " << options.eTestType   << std::endl
                    << kOptionNumOfTestItems  << ": " << options.iDataSize   << std::endl
                    << kOptionNumberOfThreads << ": " << options.iThreadsCnt << std::endl;
        }
    }
    return bRes;
}
