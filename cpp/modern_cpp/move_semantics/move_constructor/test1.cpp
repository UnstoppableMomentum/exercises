#include "test1.h"
#include "../../../../base/logs.h"

static int counter = 0;
class A {
public:

    A()
        :id(counter++)
    {
        LOG_DBG("id: %d", id);
        pointer_ = new int;
    }

    ~A()
    {
        LOG_DBG("id: %d", id);
        delete pointer_;
    }

    A(A&& a)
        :id(counter++)
    {
        LOG_DBG("id: %d", id);
        // Steal the memory, null out |a|
        pointer_ = a.pointer_;
        // 5. without null out |a| get error on destructor:
        //    "double free or corruption"
        a.pointer_ = nullptr;
        // 6. to implement move semantic:
        //   - memset arrays
        //   - vector::swap
        //   - etc.
    }

    // 1. Copy constructor is implicitly deleted.
    // A(const A& other) = delete;


private:
    int id;
    int* pointer_;
};

A CreateA(int i)
{
    LOG_FUNC();

    // 2. This is here to circumvent some compiler optimizations,
    // to ensure that we will actually call a move constructor.
    if (i % 2) {
        A a;
        return a;
    }
    A a;
    return a;
}

void ProcessA(A a)
{
    LOG_FUNC();
}

void Test1()
{
    LOG_BEG();
    // 3. CreateA returns an rvalue A.
    // Both examples below call our move constructor.
    {
        A a = CreateA(2);
    }
    LOG_BR();
    ProcessA(CreateA(2));
    //OUTPUT:
    //    A CreateA(int)
    //    A::A()id: 0
    //    A::A(A&&)id: 1
    //    A::~A()id: 0
    //    A::~A()id: 1
    //    ----------------
    //    A CreateA(int)
    //    A::A()id: 2
    //    A::A(A&&)id: 3
    //    A::~A()id: 2
    //    void ProcessA(A)
    //    A::~A()id: 3

    // OUTPUT WITH COPY CONSTRUCTOR:
    //    A CreateA(int)
    //    A::A()id: 0
    // -->A::A(const A&)id: 1
    //    A::~A()id: 0
    //    A::~A()id: 1
    //    ----------------
    //    A CreateA(int)
    //    A::A()id: 2
    // -->A::A(const A&)id: 3
    //    A::~A()id: 2
    //    void ProcessA(A)
    //    A::~A()id: 3
}

void Test1_1()
{
    LOG_BEG();
    {
        A a1;
        // 4. error: use of deleted function ‘constexpr A::A(const A&)’
        //    note: ‘constexpr A::A(const A&)’ is implicitly declared as deleted
        //    because ‘A’ declares a move ctor or move assignment operator
        // A a2 = a1;

        // 5. There is no copy ctor so use std::move
        A a2 = std::move(a1);

        //OUTPUT:
        //    A::A()id: 4
        //    A::A(A&&)id: 5
        //    A::~A()id: 5
        //    A::~A()id: 4
    }
    LOG_END();
}
