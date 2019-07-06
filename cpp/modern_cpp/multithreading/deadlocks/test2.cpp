#include "test2.h"
#include "logs.h"

#include <algorithm>
#include <mutex>
#include <thread>
#include <vector>

namespace {

class B;
void MySwap(int threadId, B& lhs, B& rhs);

class B {
public:
    B(int data)
        : data_(data)
    {
    }

    friend void MySwap(int threadId, B& lhs, B& rhs)
    {
        if(&lhs==&rhs)
            return;

        // 3. don't actually take the locks yet
        std::unique_lock<std::mutex> lock_a(lhs.m_, std::defer_lock);
        std::unique_lock<std::mutex> lock_b(rhs.m_, std::defer_lock);

        // 4. lock both unique_locks without deadlock
        std::lock(lock_a,lock_b);

        LOG_DBG("BEFORE swap threadId:%d b1.data_:%d b2.data_:%d", threadId, lhs.data_, rhs.data_);
        std::swap(lhs.data_,rhs.data_);
        LOG_DBG("AFTER swap threadId:%d b1.data_:%d b2.data_:%d", threadId, lhs.data_, rhs.data_);
    }

    int data_;
    std::mutex m_;
};

void ThreadFunc(int threadId, B& b1, B& b2)
{
    LOG_BEG();
    MySwap(threadId, b1, b2);
    LOG_END();
}

void example2()
{
    LOG_BEG();

    B b1(1);
    B b2(2);

    std::thread t1(ThreadFunc, 1, std::ref(b1), std::ref(b2));
    std::thread t2(ThreadFunc, 2, std::ref(b1), std::ref(b2));
    t1.join();
    t2.join();

    LOG_DBG("b1.data_:%d", b1.data_);
    LOG_DBG("b2.data_:%d", b2.data_);
// OUTPUT
//    void {anonymous}::ThreadFunc(int, {anonymous}::B&, {anonymous}::B&)>>>
//    void {anonymous}::MySwap(int, {anonymous}::B&, {anonymous}::B&)BEFORE swap threadId:2 b1.data_:1 b2.data_:2
//    void {anonymous}::MySwap(int, {anonymous}::B&, {anonymous}::B&)AFTER swap threadId:2 b1.data_:2 b2.data_:1
//    void {anonymous}::ThreadFunc(int, {anonymous}::B&, {anonymous}::B&)>>>
//    void {anonymous}::ThreadFunc(int, {anonymous}::B&, {anonymous}::B&)
//    void {anonymous}::MySwap(int, {anonymous}::B&, {anonymous}::B&)BEFORE swap threadId:1 b1.data_:2 b2.data_:1
//    void {anonymous}::MySwap(int, {anonymous}::B&, {anonymous}::B&)AFTER swap threadId:1 b1.data_:1 b2.data_:2
//    void {anonymous}::ThreadFunc(int, {anonymous}::B&, {anonymous}::B&)<<<
//    void {anonymous}::example2()b1.data_:1
//    void {anonymous}::example2()b2.data_:2
    LOG_END()
}

} // namespace

void Test2() {
    LOG_BEG();
    example2();
    LOG_END()
}

