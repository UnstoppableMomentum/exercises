#include "test1.h"
#include "logs.h"

#include <chrono>
#include <future>
#include <thread>
#include <functional>

namespace {

int Task1()
{
    LOG_BEG();
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(2s);
    LOG_END();
    return 1;
}

int Task2(int i)
{
    LOG_BEG();
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(3s);
    LOG_END();
    return i * 2;
}

void Example0()
{
    LOG_BEG();
    std::packaged_task<int()> pkg_task1(Task1);
    std::future<int> future1 = pkg_task1.get_future();
    pkg_task1();
    std::cout << "future1:" << future1.get() << std::endl;
    LOG_END();
}

void Example1()
{
    LOG_BEG();
    std::packaged_task<int()> pkg_task1(std::bind(Task2, 5));
    std::future<int> future1 = pkg_task1.get_future();
    pkg_task1();
    std::cout << "future1:" << future1.get() << std::endl;
    LOG_END();
}

void Example2()
{
    LOG_BEG();
    std::packaged_task<int(int)> pkg_task1([] (int i) {
        LOG_BEG();
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(3s);
        LOG_END();
        return i * 2;
    });
    std::future<int> future1 = pkg_task1.get_future();
    pkg_task1(3);
    std::cout << "future1:" << future1.get() << std::endl;
    LOG_END();
}

} // namespace

void Test1() {
    LOG_BEG();
    Example0();
    Example1();
    Example2();
    LOG_END();
}

