#include "test1.h"
#include "logs.h"

#include <chrono>
#include <future>
#include <thread>

namespace {

int Task1()
{
    LOG_BEG();
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(2s);
    LOG_END();
    return 1;
}

int Task2()
{
    LOG_BEG();
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(3s);
    LOG_END();
    return 2;
}

void Example1()
{
    LOG_BEG();
    std::future<int> futureTask1 = std::async(Task1);
    Task2();
    std::cout << "result of Task1:" << futureTask1.get() << std::endl;
    LOG_END();
}

} // namespace

void Test1() {
    LOG_BEG();
    Example1();
    LOG_END();
}

