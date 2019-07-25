#include "test2.h"
#include "logs.h"

#include <algorithm>
#include <mutex>
#include <thread>
#include <vector>
#include <condition_variable>

namespace {

std::mutex gMtx;
std::condition_variable condRead;

bool bReady {false};

void Read()
{
    LOG_BEG();
    // 1. use unique_lock with condition_variable
    std::unique_lock<std::mutex> lck(gMtx);
    condRead.wait(lck, [] {
        LOG_FUNC();
        return bReady;
    });
    LOG_END();
}

void Write()
{
    LOG_BEG();
    {
        // 2. without this lock we will get deadlock
        std::lock_guard<std::mutex> lck(gMtx);
        bReady = true;
    }
    condRead.notify_one();
    LOG_END();
}

} // namespace


void Test2() {
    LOG_BEG();
    std::thread t1(Read);
    std::thread t2(Write);
    t1.join();
    t2.join();

// OUTPUT MAY BE DIFFERENT:
//    void Test2()>>>
//    void {anonymous}::Read()>>>
//    {anonymous}::Read()::<lambda()>
//    void {anonymous}::Write()>>>
//    void {anonymous}::Write()<<<
//    {anonymous}::Read()::<lambda()>
//    void {anonymous}::Read()<<<
//    void Test2()<<<
//
//    void Test2()>>>
//    void {anonymous}::Read()>>>
//    {anonymous}::Read()::<lambda()>
//    void {anonymous}::Write()>>>
//    {anonymous}::Read()::<lambda()>
//    void {anonymous}::Read()<<<
//    void {anonymous}::Write()<<<
//    void Test2()<<<
//
//    void Test2()>>>
//    void {anonymous}::Write()>>>
//    void {anonymous}::Write()<<<
//    void {anonymous}::Read()>>>
//    {anonymous}::Read()::<lambda()>
//    void {anonymous}::Read()<<<
//    void Test2()<<<
//
//
//    The wait workflow:
//    In the initial processing of wait, the thread locks the mutex and then checks the predicate []{ return dataReady; }.
//    If the call of the predicated evaluates to
//      true: the thread continues its work.
//      false: condVar.wait() !!! UNLOCKS the mutex and puts the thread in a waiting (blocking) state
//      If the condition_variable condVar is in the waiting state and gets a notification or
//      a spurious wakeup the following steps happen.

//    The thread is unblocked and will reacquire the lock on the mutex.
//    The thread checks the predicate.
//    If the call of the predicated evaluates to
//      true: the thread continues its work.
//      false: condVar.wait() !!!UNLOCK the mutex and puts the thread in a waiting (blocking) state.
    LOG_END();
}

