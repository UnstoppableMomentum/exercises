#include "test1.h"
#include "logs.h"

#include <algorithm>
#include <thread>
#include <vector>

namespace {

void ThreadFunc()
{
    LOG_FUNC();
}

void ThreadFuncWithArg(int arg)
{
    LOG_DBG("arg:%d", arg);
}

void ThreadFuncModifyArg(int& arg)
{
    LOG_DBG("arg:%d", arg);
    ++arg;
}

// run a thread
void example1()
{
    LOG_BEG();
    std::thread t(ThreadFunc);
    t.join();
    LOG_END()
}

// lamda thread functions
void example2()
{
    LOG_BEG();
    std::thread t([](){
        LOG_FUNC();
    });
    t.join();
    // OUTPUT:
    //   example2()::<lambda()>
    LOG_END();
}

// Run and wait for multiple threads
// Pass data to a thread function
void example3()
{
    LOG_BEG();
    enum { THREADS_NUM = 3 };

    std::vector<std::thread> threads(THREADS_NUM);

    for (int i = 0; i < THREADS_NUM; ++i) {
        threads[i]=std::thread(ThreadFuncWithArg, i);
    }

    std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
// OUTPUT
//    void {anonymous}::ThreadFuncWithArg(int)arg:2
//    void {anonymous}::ThreadFuncWithArg(int)arg:1
//    void {anonymous}::ThreadFuncWithArg(int)arg:0
    LOG_END();
}

// Pass data to a thread function with std::ref
// modify parameters by lamda function
void example4()
{
    LOG_BEG();
    int i = 1;
    std::thread t(ThreadFuncModifyArg, std::ref(i));
    t.join();
    std::cout << "i:" << i << std::endl;
// OUTPUT:
//    void {anonymous}::ThreadFuncModifyArg(int&)arg:1
//    i:2
    LOG_END();
}

} // namespace

void Test1() {
    LOG_BEG();
    example1();
    example2();
    example3();
    example4();
    LOG_END()
}

