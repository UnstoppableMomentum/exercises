#include "test1.h"
#include "../../../../base/logs.h"

static int counterB = 1;

class B {
public:

    B()
        : id(counterB++)
        , data(0)
    {
        LOG_DBG("id: %d", id);
    }

    B(int i)
        : id(i)
        , data(0)
    {
        LOG_DBG("id: %d", id);
    }

    ~B()
    {
        LOG_DBG("id: %d", id);
    }


    B(const B& a)
        : id(counterB++)
        , data(0)
    {
        LOG_DBG("id: %d", id);
    }

    //private:
    int id;
    int data;
};

void Store(const B& b) {
    LOG_DBG("[%p] b.data %d", &b,  b.data);
}

template <typename T>
void ProcessAndStoreB(T& b)
{
    LOG_BEG();
    // Process
    b.data = b.id * 10;
    LOG_DBG("[%p] b.data: %d", &b, b.data);
    Store(b);
    LOG_END();
}

void Test2()
{
    LOG_BEG();
    B b;
    ProcessAndStoreB(b);
    // 1.
    // if "by value" version is defined "ProcessAndStoreB(T b)" we get error:
    //    call of overloaded ‘ProcessAndStoreB(B&)’ is ambiguous

    LOG_BR();
    // 2. error: invalid initialization of non-const reference of type ‘B&’ from an rvalue of type ‘B’
    // so we need another version of ProcessAndStoreB
    // ProcessAndStoreB(B());
    LOG_END();

}


