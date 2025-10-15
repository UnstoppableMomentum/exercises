#include "test1.h"
#include "../../../base/logs.h"

// Terminator function.
// The base case: we just have a single number.
// Required base case: prevents compilation error for missing sum() overload
// Error without this function: no matching function for call to 'sum()'
template <typename T>
double sum(T t)
{
    LOG_FUNC();
    std::cout << "t:" << t << std::endl;
    return t;
}

// The recursive case: we take a number, alongside
// some other numbers, and produce their sum.
template <typename T, typename... Rest>
double sum(T t, Rest... rest)
{
    LOG_FUNC();
    std::cout << "t:" << t << std::endl;
    return t + sum(rest...);
}

void Test1()
{
    auto a = sum(1, 2.0, 3L);
    // the expression above expands in the following way:
    //    sum(1, 2.0, 3L);
    //    1 + sum(2.0, 3L);
    //    1 + (2.0 + sum(3L));
    //    1 + (2.0 + (3L));

    std::cout << "a:" << a << std::endl;
    // OUTPUT:
    //    double sum(T, Rest ...) [with T = int; Rest = {double, long int}]
    //    t:1
    //    double sum(T, Rest ...) [with T = double; Rest = {long int}]
    //    t:2
    //    double sum(T) [with T = long int]
    //    t:3
    //    a:6
}
