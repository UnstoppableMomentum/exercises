#include "test1.h"
#include "../../../../base/logs.h"

#include <cstdio>
#include <utility>

static int counter = 1;

class A {
public:

    A()
        : id(counter++)
        , data(0)
    {
        LOG_DBG("id: %d", id);
    }

    A(int i)
        : id(i)
        , data(0)
    {
        LOG_DBG("id: %d", id);
    }

    ~A()
    {
        LOG_DBG("id: %d", id);
    }

    A(A&& a)
        : id(counter++)
        , data(0)
    {
        LOG_DBG("MOVE id: %d", id);
    }

    A(const A& a)
        : id(counter++)
        , data(0)
    {
        LOG_DBG("id: %d", id);
    }

    //private:
    int id;
    int data;
};

void Store(const A& a) {
    LOG_DBG("COPY: [%p] a.data %d", &a,  a.data);
}

void Store(A&& a) {
    LOG_DBG("MOVE: [%p] a.data: %d", &a, a.data);
}

template <typename T>
void ProcessAndStore(T&& a)
{
    LOG_BEG();
    // Process
    a.data = a.id * 10;
    LOG_DBG("[%p] a.data: %d", &a, a.data);

    // ...

    // 1.
    // The type of |a| could be an rvalue reference, which means we should pass
    // an rvalue to Store. However, it could also be an lvalue reference, which
    // means we should pass an lvalue.
    // Note that just doing Store(a); will always pass an lvalue and doing
    // Store(std::move(a)) will always pass an rvalue. Forward does the right
    // thing by casting to rvalue only if a is an rvalue reference.
    Store(std::forward<T>(a));
    LOG_END();
}


void Test1()
{    
    LOG_BEG();
    A a;
    // 2. In ProcessAndStore: T = A&,  a = A&
    ProcessAndStore(a);
    LOG_BR();
    // 3. In ProcessAndStore: T = A, a = A&&
    ProcessAndStore(A());
    LOG_BR();
    // 4. In ProcessAndStore: T = A, a = A&&
    ProcessAndStore<A>(33);
    LOG_END();

//OUTPUT:
//    void Test1()>>>
//    A::A()id: 1
//    void ProcessAndStore(T&&) [with T = A&]>>>
//    void ProcessAndStore(T&&) [with T = A&][0x7ffe5e45f220] a.data: 10
//    void Store(const A&)COPY: [0x7ffe5e45f220] a.data 10
//    void ProcessAndStore(T&&) [with T = A&]<<<
//    ----------------
//    A::A()id: 2
//    void ProcessAndStore(T&&) [with T = A]>>>
//    void ProcessAndStore(T&&) [with T = A][0x7ffe5e45f230] a.data: 20
//    void Store(A&&)MOVE: [0x7ffe5e45f230] a.data: 20
//    void ProcessAndStore(T&&) [with T = A]<<<
//    A::~A()id: 2
//    ----------------
//    A::A(int)id: 33
//    void ProcessAndStore(T&&) [with T = A]>>>
//    void ProcessAndStore(T&&) [with T = A][0x7ffe5e45f240] a.data: 330
//    void Store(A&&)MOVE: [0x7ffe5e45f240] a.data: 330
//    void ProcessAndStore(T&&) [with T = A]<<<
//    A::~A()id: 33
//    void Test1()<<<
//?-->A::~A()id: 1
}


