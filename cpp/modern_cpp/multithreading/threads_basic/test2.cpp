#include "test2.h"
#include "logs.h"
#include <thread>

namespace {

void thread_func()
{
    LOG_FUNC();
}

} // namespace


// scoped_thread class:
// Using RAII to wait for a thread to complete
class scoped_thread
{
    std::thread t;
public:
    explicit scoped_thread(std::thread t_):
        t(std::move(t_))
    {
        LOG_FUNC();
        if(!t.joinable())
            throw std::logic_error("No thread");
    }
    ~scoped_thread()
    {
        LOG_BEG();
        t.join();
        LOG_END();
    }
    scoped_thread(scoped_thread const&)=delete;
    scoped_thread& operator=(scoped_thread const&)=delete;
};

void example2()
{
    LOG_BEG();
    scoped_thread(std::thread(thread_func));
    std::cout << "do somth ..." << std::endl;
    LOG_END();
}

void Test2()
{
    LOG_BEG();
    example2();
// OUTPUT
//    scoped_thread::scoped_thread(std::thread)
//    scoped_thread::~scoped_thread()>>>
//    void {anonymous}::thread_func()
//    scoped_thread::~scoped_thread()<<<
//    do somth ...
    LOG_END();
}

