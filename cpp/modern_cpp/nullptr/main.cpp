// Prefer nullptr to 0 and NULL

#include <iostream>
#include <random>
#include <memory>
#include <thread>
#include <mutex>

void qqq(int i)
{
    std::cout << __PRETTY_FUNCTION__ << " i:" << i << std::endl;
}
void qqq(bool b)
{
    std::cout << __PRETTY_FUNCTION__ << " b:" << b << std::endl;
}
void qqq(void * p)
{
    std::cout << __PRETTY_FUNCTION__ << " p:" << p << std::endl;
}

void Test1()
{
    std::cout << "===" << __PRETTY_FUNCTION__ << "==="  << std::endl;

    // OK
    qqq(0);

    // 1. error: call of overloaded ‘qqq(NULL)’ is ambiguous
    // qqq(NULL); // this never calls qqq(void*)
    //
    //#ifdef __GNUG__
    //#define NULL __null
    //#else   /* G++ */
    //#ifndef __cplusplus
    //#define NULL ((void *)0)
    //#else   /* C++ */
    //#define NULL 0
    //#endif  /* C++ */
    //
    // MY CASE IS __GNUG__  __null
    // The implementation of __null is as a G++ internal.

    // ?: calls  qqq(bool)
    const char * p = 0;
    qqq(p);

    // OK: this works as expected
    qqq(nullptr);

    //    OUTPUT:
    //    void qqq(int) i:0
    //    void qqq(bool) b:0
    //    void qqq(void*) p:0
}

class someObj
{
public:
    int id = 333222;
};

someObj * getObj()
{
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> dis(1, 2);
    static someObj obj;

    someObj* pRes = nullptr;
    if(0 == dis(gen) % 2) {
        pRes = &obj;
    }
    return pRes;
}

void Test2 ()
{
    std::cout << "===" << __PRETTY_FUNCTION__ << "==="  << std::endl;
    for (int i = 0; i < 5; ++i) {
        auto a = getObj();
        // 2. ?:  pointer or integral?
        // if (0 == a) {...}

        // 3. This is better: auto is a pointer type, not an integral type
        if (nullptr == a) {
            std::cout << "null pointer"  << std::endl;
        } else {
            // Do something
        }
    }
}

std::mutex f1m;// use only with f1
int f1(std::shared_ptr<someObj> sp);


std::mutex f2m;// use only with f2
double f2 ( std::unique_ptr<someObj> up);

std::mutex f3m;// use only with f3
bool f3 (someObj* p);


int f1(std::shared_ptr<someObj> sp)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return 1;
}

double f2( std::unique_ptr<someObj> up)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return 2.0;
}

bool f3(someObj* p)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return true;
}

using MuxGuard = std::lock_guard<std::mutex>;
void Test3()
{
    std::cout << "===" << __PRETTY_FUNCTION__ << "==="  << std::endl;
    // 4. 0, NULL, nullptr are possible.
    // copy - paste, not a good style
    //=======================
    {
        MuxGuard g(f1m);
        auto a = f1(0);
        std::cout << " a:" << a << std::endl;
    }
    {
        MuxGuard g(f1m);
        auto a = f2(0);
        std::cout << " a:" << a << std::endl;
    }
    {
        MuxGuard g(f1m);
        auto a = f3(0);
        std::cout << " a:" << a << std::endl;
    }
    //=======================
    {
        MuxGuard g(f1m);
        auto a = f1(NULL);
        std::cout << " a:" << a << std::endl;
    }
    {
        MuxGuard g(f1m);
        auto a = f2(NULL);
        std::cout << " a:" << a << std::endl;
    }
    {
        MuxGuard g(f1m);
        auto a = f3(NULL);
        std::cout << " a:" << a << std::endl;
    }
    //=======================
    {
        MuxGuard g(f1m);
        auto a = f1(nullptr);
        std::cout << " a:" << a << std::endl;
    }
    {
        MuxGuard g(f1m);
        auto a = f2(nullptr);
        std::cout << " a:" << a << std::endl;
    }
    {
        MuxGuard g(f1m);
        auto a = f3(nullptr);
        std::cout << " a:" << a << std::endl;
    }
}

// C++11
// use template to avoid code duplication
// pass function as a parameter, return the function result
template<typename FuncType,
         typename MuxType,
         typename PtrType>
auto lockAndCall_CPP11(FuncType func,
                       MuxType& mutex,
                       PtrType ptr) -> decltype(func(ptr))
{
    std::cout << "===" << __PRETTY_FUNCTION__ << "==="  << std::endl;
    MuxGuard g(mutex);
    return func(ptr);
}

// C++11
void Test4()
{
    std::cout << "===" << __PRETTY_FUNCTION__ << "==="  << std::endl;

    // 5. error: no matching function for call to ‘lockAndCall(int (&)(std::shared_ptr<someObj>), std::mutex&, int)’
    // auto resultInt = lockAndCall_CPP11(f1, f1m, 0);

    // 6. error: no matching function for call to ‘lockAndCall(double (&)(std::unique_ptr<someObj>), std::mutex&, NULL)’
    // auto resultNULL = lockAndCall_CPP11(f2, f2m, NULL);

    // 7. OK
    auto result1 = lockAndCall_CPP11(f1, f2m, nullptr);
    auto result2 = lockAndCall_CPP11(f2, f2m, nullptr);
    auto result3 = lockAndCall_CPP11(f3, f3m, nullptr);
    std::cout
            << "result1:" << result1 << std::endl
            << "result2:" << result2 << std::endl
            << "result3:" << result3 << std::endl;

}

// C++14
// use template to avoid code duplication
// pass function as a parameter, return the function result
template<typename FuncType,
         typename MuxType,
         typename PtrType>
decltype(auto) lockAndCall_CPP14(FuncType func,
                                 MuxType& mutex,
                                 PtrType ptr)
{
    std::cout << "===" << __PRETTY_FUNCTION__ << "==="  << std::endl;
    MuxGuard g(mutex);
    return func(ptr);
}

// C++14
void Test5()
{
    std::cout << "===" << __PRETTY_FUNCTION__ << "==="  << std::endl;

    // 5. error: could not convert ‘ptr’ from ‘int’ to ‘std::shared_ptr<someObj>’
    // auto resultInt = lockAndCall_CPP14(f1, f1m, 0);

    // 6. error:  error: could not convert ‘ptr’ from ‘long int’ to ‘std::unique_ptr<someObj>’
    // auto resultNULL = lockAndCall_CPP14(f2, f2m, NULL);

    // 7. OK
    auto result1 = lockAndCall_CPP14(f1, f2m, nullptr);
    auto result2 = lockAndCall_CPP14(f2, f2m, nullptr);
    auto result3 = lockAndCall_CPP14(f3, f3m, nullptr);
    std::cout
            << "result1:" << result1 << std::endl
            << "result2:" << result2 << std::endl
            << "result3:" << result3 << std::endl;

}

int main(int argc, char *argv[])
{
    std::cout << __PRETTY_FUNCTION__ << ">>>" << std::endl;
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
    std::cout << __PRETTY_FUNCTION__ << "<<<" << std::endl;
    return 0;
}
