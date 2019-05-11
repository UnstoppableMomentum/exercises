#include "test1.h"
#include "../../../base/logs.h"

template<typename _TN>
class CheckIsClassT
{
private:
    typedef char TOne;
    typedef struct { char a[2]; } TTwo;
    template <typename C> static TOne Test(int C::*) { return TOne();}
    template <typename C> static TTwo Test(...) { return TTwo(); }
public:
    static const bool IsClass = sizeof(CheckIsClassT<_TN>::Test<_TN>(0)) == sizeof(TOne);
};

class A { int i; };
struct B { char b; };
enum MyEnum { one, two };
union MyUnion { int a; char b; };

void Test1()
{
    LOG_BEG();
    LOG_DBG_0("CheckIsClassT<int>::IsClass:%d", CheckIsClassT<int>::IsClass);
    LOG_DBG_0("CheckIsClassT<A>::IsClass:%d", CheckIsClassT<A>::IsClass);
    LOG_DBG_0("CheckIsClassT<B>::IsClass:%d", CheckIsClassT<B>::IsClass);
    LOG_DBG_0("CheckIsClassT<MyEnum>::IsClass:%d", CheckIsClassT<MyEnum>::IsClass);
    LOG_DBG_0("CheckIsClassT<MyUnion>::IsClass:%d", CheckIsClassT<MyUnion>::IsClass);
    LOG_END();
// OUTPUT:
//    CheckIsClassT<int>::IsClass:0
//    CheckIsClassT<A>::IsClass:1
//    CheckIsClassT<B>::IsClass:1
//    CheckIsClassT<MyEnum>::IsClass:0
//    CheckIsClassT<MyUnion>::IsClass:1
}
