#include "test1.h"
#include "../../../../base/logs.h"

static int counter3 = 0;
class C {
public:

    C()
        :id(counter3++)
    {
        LOG_DBG("id: %d", id);
        pointer_ = new int;
        *pointer_ = counter3;
    }

    ~C()
    {
        LOG_DBG("id: %d", id);
        delete pointer_;
    }

    C(const C& c)
        :id(counter3++)
    {
        LOG_DBG("id: %d", id);
        // 1. copy data
        pointer_ = new int;
        *pointer_ = *c.pointer_;
    }

    // 1. Copy constructor is implicitly deleted.
    // A(const A& other) = delete;

private:
    int id;
    int* pointer_;
};

C CreateC(int i)
{
    LOG_FUNC();

    // 2. This is here to circumvent some compiler optimizations,
    // to ensure that we will actually call a move constructor.
    if (i % 2) {
        C c;
        return c;
    }
    C c;
    return c;
}

void ProcessC(C c)
{
    LOG_FUNC();
}


void Test3()
{
    // Copy constructors can also bind to rvalues (with lower priority).
    LOG_BEG();
    {
        C c;
        // std::move casts |c| to an rvalue, but since there is no move
        // constructor, the copy constructor is used.
        C c2 = std::move(c);
    }
    LOG_BR();
    {
        // CreateC returns an rvalue, but since there is no move constructor, the
        // copy constructor is used.
        ProcessC(CreateC(2));
        // std::move casts |c| to an rvalue, but since there is no move
        // constructor, the copy constructor is used.
        C c;
        ProcessC(std::move(c));
    }
    LOG_END();
}

// class D
// Move constructors will only bind to non-const rvalues.
class D {
public:
    D()
        :id(counter3++)
    {
        LOG_DBG("id: %d", id);
    }
    D(const D& d)
        :id(counter3++)
    {
        LOG_DBG("id: %d", id);
    }

    D(D&& d)
        :id(counter3++)
    {
        LOG_DBG("id: %d", id);
    }

    ~D()
    {
        LOG_DBG("id: %d", id);
    }
private:
    int id;
};

D CreateD(int i)
{
    LOG_FUNC();

    // 2. This is here to circumvent some compiler optimizations,
    // to ensure that we will actually call a move constructor.
    if (i % 2) {
        D d;
        return d;
    }
    D d;
    return d;
}

void ProcessD(D d)
{
    LOG_FUNC();
}

void Test3_1()
{
    LOG_BEG();
    {
        const D d = CreateD(2);
        // std::move casts to an rvalue, but since this is const, it becomes an rvalue
        // to const, which uses the copy constructor, not the move constructor.
        ProcessD(std::move(d));
    }
    LOG_BR();
    {
        D d = CreateD(2);
        // move ctor is called, d is non-const
        ProcessD(std::move(d));
    }
    LOG_END();

//OUTPUT:
//    D CreateD(int)
//    D::D()id: 6
//    D::D(D&&)id: 7
//    D::~D()id: 6
// -->D::D(const D&)id: 8
//    void ProcessD(D)
//    D::~D()id: 8
//    D::~D()id: 7
//    ----------------
//    D CreateD(int)
//    D::D()id: 9
//    D::D(D&&)id: 10
//    D::~D()id: 9
// -->D::D(D&&)id: 11
//    void ProcessD(D)
//    D::~D()id: 11
//    D::~D()id: 10
}

