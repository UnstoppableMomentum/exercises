#include "test2.h"
#include "logs.h"

#include <chrono>
#include <future>
#include <thread>
#include <string>

namespace {

class A {
 public:
    A() : m_s("intial val") {}

    int Task1(int i, const std::string& s) {
        LOG_BEG();
        m_s = s;
        std::cout << "i:" << i << " " << s << std::endl;
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(2s);
        LOG_END();
        return 1;
    }

    int Task2(const std::string& s) {
        LOG_BEG();
        m_s = s;
        std::cout << s << std::endl;
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(3s);
        LOG_END();
        return 2;
    }
    std::string m_s;
};

void Example2() {
    LOG_BEG();
    A a;
    A a1;
    auto futureTask1 = std::async(&A::Task1, a, 322223, "Qwerty!");
    auto futureTask2 = std::async(&A::Task2, &a1, "Qwerty222!");
    // DOSMTH
    std::cout << "result of Task1():" << futureTask1.get()
              << " a.m_s:'" << a.m_s << "'" << std::endl;

    std::cout << "result of Task2():" << futureTask2.get()
              << " a1.m_s:'" << a1.m_s << "'" << std::endl;

    LOG_END();
}

}  // namespace

void Test2() {
    LOG_BEG();
    Example2();
    LOG_END();
}

