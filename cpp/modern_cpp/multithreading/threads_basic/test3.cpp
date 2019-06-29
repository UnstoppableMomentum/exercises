#include <algorithm>
#include <thread>

#include "test3.h"
#include "logs.h"

static int counter = 0;
static int counter2 = 0;

// use of functor for C++ STL thread
class FunctorDbg
{
public:
    FunctorDbg()
        : _value(0)
        , _id(counter++)
    {
        LOG_DBG(" this:%p  counters:[%d:%d] _value:%d _id:%d", this, counter, counter2, _value, _id);
    }


    FunctorDbg(const FunctorDbg& other)
        :_id(counter2++)
    {
        LOG_DBG(" this:%p other:%p counter:%d  _value:%d _id:%d",
                this, other, counter, _value, _id);
    }

    FunctorDbg(FunctorDbg&& other)
        :_id(counter2++)
    {
        LOG_DBG(" this:%p other:%p counter:%d  _value:%d _id:%d",
                this, other, counter, _value, _id);
        // Note that although the type of |other| is an rvalue reference, |other|
        // itself is an lvalue, since it is a named object. In order to ensure that
        // the move assignment is used, we have to explicitly specify
        // std::move(other).
        *this = std::move(other);
    }

    FunctorDbg& operator = (const FunctorDbg& other)
    {
        LOG_DBG(" this:%p other:%p counter:%d  _value:%d _id:%d",
                this, other, counter, _value, _id);
        return *this;
    }

    FunctorDbg& operator = (FunctorDbg&& other)
    {
        LOG_DBG(" this:%p other:%p counter:%d  _value:%d _id:%d",
                this, other, counter, _value, _id);
        return *this;
    }

    ~FunctorDbg()
    {
        LOG_DBG(" this:%p  _value:%d _id:%d", this, _value, _id);
    }

    void operator()(unsigned int value)
    {
        ++value;
        _value = value;
        LOG_DBG(" this:%p  _value:%d _id:%d", this, _value, _id);
    }

    unsigned int get_value()
    {
        LOG_DBG(" this:%p  _value:%d _id:%d", this, _value, _id);
        return _value;
    }

private:
    int _value;
    int _id;
};


class Functor
{
public:
    void operator()(unsigned int value)
    {
        ++value;
        _value = value;
        LOG_DBG(" this:%p  _value:%d _id:%d", this, _value, _id);
    }

    unsigned int get_value()
    {
        LOG_DBG(" this:%p  _value:%d _id:%d", this, _value, _id);
        return _value;
    }

private:
    int _value;
    int _id;
};

void example5()
{
    LOG_BEG();
    int i = 1;
    Functor f;
    std::thread t(std::ref(f), i);
    // !!!
    // In case of std::thread t(f, i);
    // f object passed to thread function is different:
    t.join();
    std::cout
            << "Use of functor for C++ STL thread" << std::endl
            << " f.get_value():" << f.get_value()
            << " f:" << &f
            << std::endl;
    // OUTPUT:
    //    void Functor::operator()(unsigned int) this:0x7fffffffe100  _value:2 _id:32767
    //    unsigned int Functor::get_value() this:0x7fffffffe100  _value:2 _id:32767
    //     f.get_value():2 f:0x7fffffffe100
    LOG_END();
}

void Test3() {
    LOG_BEG();
    example5();
    LOG_END()
}
