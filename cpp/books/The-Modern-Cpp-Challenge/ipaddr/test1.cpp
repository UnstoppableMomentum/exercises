#include "test1.h"

#include <chrono>
#include <future>
#include <thread>
#include <functional>

#include "logs.h"
#include "ipaddr.h"

namespace {


} // namespace

void Test1() {
    LOG_BEG();
    {
        IpV4 ip;
        std::cout << "ip:"<< ip.ToString() << std::endl;
    }
    {
        IpV4 ip(172,26,123,133);
        std::cout << "ip:"<< ip.ToString() << std::endl;
    }
    {
        IpV4 ip;
        std::cin >> ip;
        if(!std::cin.fail()) {
            std::cout << ip << std::endl;
        } else {
            std::cout << "ERROR: cin >> ip:"<< ip.ToString() << std::endl;
        }
    }

    LOG_END();
}

