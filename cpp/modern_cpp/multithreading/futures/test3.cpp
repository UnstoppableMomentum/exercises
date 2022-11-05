#include "test3.h"

#include "logs.h"
#include "move_only_class.h"

#include <chrono>
#include <future>
#include <thread>
#include <string>

namespace {

class A {
 public:
    A() : m_d(0.0) {}
    explicit A(double d) : m_d(d) {}

    double operator() (double d) {
        LOG_BEG();
        std::cout << "000 m_d:" << m_d << std::endl;
        m_d = d;
        std::cout << "001 m_d:" << m_d << std::endl;
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(2s);
        LOG_END();
        return 1;
    }
    double m_d;
};

void Example3() {
    LOG_BEG();
    // Calls temp A(2.2222) where tmpy is move-constructed from A()
    auto futureTask1 = std::async(A(), 2.2222);

    A a;
    a.m_d = 1.1111;
    auto futureTask2 = std::async(std::ref(a), 3.3333);
    // DOSMTH
    std::cout << "result of futureTask1:" << futureTask1.get() << std::endl;
    std::cout << "result of futureTask2:" << futureTask2.get()
              << " a.m_d:" << a.m_d << std::endl;

    std::future<double> futureTask3 = std::async(cpp_exercises::MoveOnlyClass(), 4.44);
    // DOSMTH
    std::cout << "result of futureTask3:" << futureTask3.get() << std::endl;

    LOG_END();
}


void Example4() {
    LOG_BEG();
    auto futureTask1 = std::async(std::launch::async   , A(), 4.44);
    // When async is used instead of deferred for futureTask2
    // the log of operator() for both task is shown immediately.
    // In case of "deferred" parameter is used the log of futureTask2
    // is shown after 2 seconds.
    auto futureTask2 = std::async(std::launch::deferred, A(), 5.55);
    // DOSMTH
    std::cout << "result of futureTask1:" << futureTask1.get() << std::endl;
    std::cout << "result of futureTask2:" << futureTask2.get() << std::endl;
    LOG_END();
}

}  // namespace

void Test3() {
    LOG_BEG();
    //Example3();
    Example4();
    LOG_END();
}

