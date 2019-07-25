#include "test3.h"

#include "logs.h"

#include <algorithm>
#include <mutex>
#include <thread>
#include <vector>
#include <condition_variable>

namespace {

std::mutex gMtx;
std::condition_variable condRead;

int iSharedVal = 0;
bool bReady {false};

void Read()
{
    LOG_BEG();
    // 1. use unique_lock with condition_variable
    std::unique_lock<std::mutex> lck(gMtx);
    condRead.wait(lck, [] {
        LOG_DBG("iSharedVal:%d thread id:%ld", iSharedVal, std::this_thread::get_id());
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
        ++iSharedVal;
        LOG_DBG("iSharedVal:%d thread id:%ld", iSharedVal, std::this_thread::get_id());
        bReady = true;
    }
    condRead.notify_one();
    LOG_END();
}

void ReadLoop()
{
    LOG_BEG();
    for(int i = 0; i < 3; ++i)
    {
        LOG_DBG("i:%d thread id:%ld", i, std::this_thread::get_id());
        Read();
    }
    LOG_END();
}

void WriteLoop()
{
    LOG_BEG();
    for(int i = 0; i < 3; ++i)
    {
        LOG_DBG("i:%d thread id:%ld", i, std::this_thread::get_id());
        {
            std::lock_guard<std::mutex> lck(gMtx);
            bReady = true;
        }
        Write();
    }
    LOG_END();
}

} // namespace


void Test3() {
    LOG_BEG();
    std::thread t1(ReadLoop);
    std::thread t2(WriteLoop);
    t1.join();
    t2.join();
    LOG_END();

// POSSIBLE OUTPUT
//    void Test3()>>>
//    void {anonymous}::ReadLoop()>>>
//    void {anonymous}::ReadLoop()i:0 thread id:139723034973952
//    void {anonymous}::Read()>>>
//    {anonymous}::Read()::<lambda()>iSharedVal:0 thread id:139723034973952
//    void {anonymous}::WriteLoop()>>>
//    void {anonymous}::WriteLoop()i:0 thread id:139723026581248
//    void {anonymous}::Write()>>>
//    void {anonymous}::Write()iSharedVal:1 thread id:139723026581248
//    void {anonymous}::Write()<<<
//    void {anonymous}::WriteLoop()i:1 thread id:139723026581248
//    void {anonymous}::Write()>>>
//    void {anonymous}::Write()iSharedVal:2 thread id:139723026581248
//    void {anonymous}::Write()<<<
//    void {anonymous}::WriteLoop()i:2 thread id:139723026581248
//    {anonymous}::Read()::<lambda()>iSharedVal:2 thread id:139723034973952
//    void {anonymous}::Read()<<<
//    void {anonymous}::Write()>>>
//    void {anonymous}::Write()iSharedVal:3 thread id:139723026581248
//    void {anonymous}::ReadLoop()i:1 thread id:139723034973952
//    void {anonymous}::Write()<<<
//    void {anonymous}::WriteLoop()<<<
//    void {anonymous}::Read()>>>
//    {anonymous}::Read()::<lambda()>iSharedVal:3 thread id:139723034973952
//    void {anonymous}::Read()<<<
//    void {anonymous}::ReadLoop()i:2 thread id:139723034973952
//    void {anonymous}::Read()>>>
//    {anonymous}::Read()::<lambda()>iSharedVal:3 thread id:139723034973952
//    void {anonymous}::Read()<<<
//    void {anonymous}::ReadLoop()<<<
//    void Test3()<<<

}

