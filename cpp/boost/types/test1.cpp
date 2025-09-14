#include <iostream>
#include <string>

#include <boost/type_index.hpp>

template <typename T>
void f(const T &param)
{
    using boost::typeindex::type_id_with_cvr;
    // Display template type info
    std::cout << "Т: " << type_id_with_cvr<T>().pretty_name() << std::endl;
    // Display function parameter type info
    std::cout << "param: " << type_id_with_cvr<decltype(param)>().pretty_name() << std::endl;
}

template <typename T>
void f2(const T &param)
{
    std::cout << param->ToString() << std::endl;
}

void test1()
{
    f(1);
    // OUTPUT:
    //     Т: int
    // param: int const&
}

void test2()
{
    int i = 1;
    int &ri(i);
    f(ri);
    // OUTPUT:
    //         Т: int
    // param: int const&
}

class A
{
public:
    std::string ToString() { return "A"; }
};

void test3()
{
    class A
    {
    };

    f(::A());
    // OUTPUT
    //     Т: A
    // param: A const&

    f(A());
    // Т: test3()::A
    // param: test3()::A const&

    ::A a;
    f(&a);
    // OUTPUT
    // Т: A*
    // param: A* const&

    f2(&a);
    // OUTPUT:
    // A

    // f2(a);
    // BUILD ERROR

    auto a1 = a;
    f(a1);
    // OUTPUT:
    // Т: A
    // param: A const&

    // f2(a1);
    // BUILD ERROR:
    // error: base operand of ‘->’ has non-pointer type ‘const A’
    // std::cout << param->ToString() << std::endl;

    auto a2 = &a;
    f(a2);
    f2(a2);
    // OUTPUT:
    // Т: A*
    // param: A* const&
    // A
}

void test_types()
{
    // test1();
    // test2();
    test3();
}