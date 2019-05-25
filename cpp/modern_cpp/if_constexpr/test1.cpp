#include "test1.h"
#include "logs.h"
#include <type_traits>

template <typename T>
void print_ver1(T val)
{
    LOG_FUNC();

    if constexpr (std::is_class_v<T>) {
        std::cout << "type is_class";
    } else {
        std::cout << "val:" << val << ", type is_arithmetic==";
        if constexpr (std::is_arithmetic_v<T>) {
            std::cout << "true";
        } else {
            std::cout << "false";
        }
    }
    std::cout << std::endl;
}


// C++17
// terminator function is not required
// based on:
// 1. compile time if: "if constexpr"
// 2.  sizeof... (args)
template<typename T, typename ... Types>
void print_ver2(T firstArg, Types ... args)
{
    LOG_FUNC();
    std::cout << firstArg << std::endl;

    // 3. Error: sizeof...(args) requires C++17
    // if (sizeof... (args) > 0)
    // 4. Error: mix compile-time features with run-time features
   if constexpr (sizeof... (args) > 0) {
        print_ver2(args ...);
   }
}

class A{
    int a;
};

void Test1() {
    print_ver1(1);
    print_ver1("qqq");
    A a;
    print_ver1(a);
    print_ver1(A());
    LOG_BR();
// OUTPUT
//    void print_ver1(T) [with T = int]
//    val:1, type is_arithmetic==true
//    void print_ver1(T) [with T = const char*]
//    val:qqq, type is_arithmetic==false
//    void print_ver1(T) [with T = A]
//    type is_class
//    void print_ver1(T) [with T = A]
//    type is_class

    print_ver2(2, "someString2", 3.2);
//OUTPUT:
//    void print_ver2(T, Types ...) [with T = int; Types = {const char*, double}]
//    2
//    void print_ver2(T, Types ...) [with T = const char*; Types = {double}]
//    someString2
//    void print_ver2(T, Types ...) [with T = double; Types = {}]
//    3.2
}
