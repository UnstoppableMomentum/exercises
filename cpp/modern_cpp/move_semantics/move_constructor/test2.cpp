#include "test2.h"
#include "../../../../base/logs.h"

static int counter2 = 0;
class B {
public:
    B()
        : id(counter2++)
        , pointer(new int)
    {
        *pointer = id;
        LOG_DBG("id: %d %p %d", id, pointer, *pointer);
    }

    ~B()
    {
        LOG_DBG("id: %d %p %d", id, pointer, (pointer ? *pointer : 0));
    }

    B(B&& other)
        :id(counter2++)
        // 1. move semantics, no allocation
        , pointer(nullptr)
    {
        LOG_BEG();
        // Note that although the type of |other| is an rvalue reference, |other|
        // itself is an lvalue, since it is a named object. In order to ensure that
        // the move assignment is used, we have to explicitly specify
        // std::move(other).
        *this = std::move(other);
        LOG_DBG("id: %d %p %d", id, pointer, *pointer);
        LOG_END();
    }

    B& operator = (B&& other)
    {
        LOG_BEG();
        // 2. !!!
        delete pointer;
        // 3. Steal the memory, null out |other|.
        pointer = other.pointer;
        other.pointer = nullptr;
        LOG_DBG("id: %d %p %d", id, pointer, *pointer);
        // 4. swap, memset, etc inner data
        // ...

        // 5. return
        LOG_END();
        return *this;
    }

private:
    int id;
    int* pointer;
};

B CreateB(int i)
{
    LOG_FUNC();

    // 1. This is here to circumvent some compiler optimizations,
    // to ensure that we will actually call a move constructor.
    if (i % 2) {
        B b;
        return b;
    }
    B b;
    return b;
}

void ProcessB(B b)
{
    LOG_FUNC();
}

void Test2()
{
    LOG_BEG();
    // MakeB returns an rvalue B.
    // Both lines below call our move constructor.
    {
        B b = CreateB(2);
    }
    LOG_BR();
    {
        ProcessB(CreateB(2));
    }
    LOG_END();
//OUTPUT:
//    B CreateB(int)
//    B::B()id: 0 0x616c30 0
//    B::B(B&&)>>>
//-->   B& B::operator=(B&&)>>>
//      B& B::operator=(B&&)id: 1 0x616c30 0
//      B& B::operator=(B&&)<<<
//--> CALL MOVE-ASSIGMENT OPERATOR
//    B::B(B&&)id: 1 0x616c30 0
//    B::B(B&&)<<<
//--> NOW THE OBJECT WITH id=1 OWNS DATA
//    B::~B()id: 0 (nil) 0
//    B::~B()id: 1 0x616c30 0
//    ----------------
//    B CreateB(int)
//    B::B()id: 2 0x616c50 2
//    B::B(B&&)>>>
//--> CALL MOVE-ASSIGMENT OPERATOR
//      B& B::operator=(B&&)>>>
//      B& B::operator=(B&&)id: 3 0x616c50 2
//      B& B::operator=(B&&)<<<
//    B::B(B&&)id: 3 0x616c50 2
//    B::B(B&&)<<<
//    B::~B()id: 2 s(nil) 0
//--> NOW THE TEMPORARY OBJECT "id=2" IS DESTROYED "id=3" OWNS DATA
//    void ProcessB(B)
//    B::~B()id: 3 0x616c50 2
}


