#include "test1.h"
#include "logs.h"

#include <algorithm>
#include <mutex>
#include <thread>
#include <vector>
#include <condition_variable>

namespace {

std::mutex gMtx;
std::condition_variable condRead;
std::condition_variable condWrite;
int iSharedVal;

void Read()
{
    std::unique_lock<std::mutex> lock(gMtx);
    while (iSharedVal == 0) {
        condRead.wait(lock);
    }
    std::cout << " iSharedVal:" << iSharedVal << std::endl;
    iSharedVal = 0;
    condWrite.notify_one();
}

void Write(int iThreadId)
{
    std::unique_lock<std::mutex> lock(gMtx);
    while (iSharedVal != 0) {
        condWrite.wait(lock);
    }
    std::cout << " iThreadId:" << iThreadId << std::endl;
    iSharedVal = iThreadId + 1;
    condRead.notify_one();
}

} // namespace

void example1()
{
    LOG_BEG();

    enum { THREADS_NUM = 10 };

    std::thread readers[THREADS_NUM];
    std::thread writers[THREADS_NUM];

    for (int i = 0 ; i < THREADS_NUM; ++i) {
        readers[i] = std::thread(Read);
        writers[i] = std::thread(Write, i);
    }

    for (int i = 0 ; i < THREADS_NUM; ++i) {
        readers[i].join();
        writers[i].join();
    }
    LOG_END();

// OUTPUT
//    void example1()>>>
//     iThreadId:0
//     iSharedVal:1
//     iThreadId:1
//     iSharedVal:2
//     iThreadId:2
//     iSharedVal:3
//     iThreadId:3
//     iSharedVal:4
//     iThreadId:4
//     iSharedVal:5
//     iThreadId:5
//     iSharedVal:6
//     iThreadId:6
//     iSharedVal:7
//     iThreadId:7
//     iSharedVal:8
//     iThreadId:8
//     iSharedVal:9
//     iThreadId:9
//     iSharedVal:10
//    void example1()<<<
//
// BUT MAY BE:
//iThreadId:0
//iSharedVal:1
//iThreadId:1
//iSharedVal:2
//iThreadId:3
//iSharedVal:4
//iThreadId:2
//iSharedVal:3
//iThreadId:4
//iSharedVal:5
//iThreadId:9
//iSharedVal:10
//iThreadId:5
//iSharedVal:6
//iThreadId:8
//iSharedVal:9
//iThreadId:6
//iSharedVal:7
//iThreadId:7
//iSharedVal:8

}


void Test1() {
    LOG_BEG();
    example1();
    LOG_END();
}

