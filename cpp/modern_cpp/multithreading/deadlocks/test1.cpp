#include "test1.h"
#include "logs.h"

#include <algorithm>
#include <mutex>
#include <thread>
#include <vector>

namespace {

class A;
void MySwap(int threadId, A& lhs, A& rhs);

class A {
 public:
    explicit A(int data)
        : data_(data) {
    }

    friend void MySwap(int threadId, A& lhs, A& rhs) {
        if (&lhs == &rhs)
            return;

        // 1. std::lock — a function that can lock two or more mutexes at once without risk of deadlock.
        std::lock(lhs.m_, rhs.m_);
        // 2. The std::adopt_lock parameter is supplied in  addition to the mutex
        // to indicate to the std::lock_guard objects that the mutexes are already locked,
        // and they should just adopt the ownership of the existing lock on
        // the mutex rather than attempt to lock the mutex in the constructor.
        std::lock_guard<std::mutex> lock_a(lhs.m_, std::adopt_lock);
        std::lock_guard<std::mutex> lock_b(rhs.m_ ,std::adopt_lock);

        LOG_DBG("BEFORE swap threadId:%d a1.data_:%d a2.data_:%d", threadId, lhs.data_, rhs.data_);
        std::swap(lhs.data_,rhs.data_);
        LOG_DBG("AFTER swap threadId:%d a1.data_:%d a2.data_:%d", threadId, lhs.data_, rhs.data_);
    }

    int data_;
    std::mutex m_;
};

void ThreadFunc(int threadId, A& a1, A& a2)
{
    LOG_BEG();
    MySwap(threadId, a1, a2);
    LOG_END();
}

void example1()
{
    LOG_BEG();

    A a1(1);
    A a2(2);

    std::thread t1(ThreadFunc, 1, std::ref(a1), std::ref(a2));
    std::thread t2(ThreadFunc, 2, std::ref(a1), std::ref(a2));
    t1.join();
    t2.join();

    LOG_DBG("a1.data_:%d", a1.data_);
    LOG_DBG("a2.data_:%d", a2.data_);

    LOG_END()
}

} // namespace

void Test1() {
    LOG_BEG();
    example1();
//OUTPUT:
//    void ThreadFunc(int, A&, A&)>>>
//    void MySwap(int, A&, A&)BEFORE swap threadId:2 a1.data_:1 a2.data_:2
//    void MySwap(int, A&, A&)AFTER swap threadId:2 a1.data_:2 a2.data_:1
//    void ThreadFunc(int, A&, A&)<<<
//    void ThreadFunc(int, A&, A&)>>>
//    void MySwap(int, A&, A&)BEFORE swap threadId:1 a1.data_:2 a2.data_:1
//    void MySwap(int, A&, A&)AFTER swap threadId:1 a1.data_:1 a2.data_:2
//    void ThreadFunc(int, A&, A&)<<<
//    void example1()a1.data_:1
//    void example1()a2.data_:2

    LOG_END()
}

