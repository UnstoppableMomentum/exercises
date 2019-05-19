#include "test2.h"
#include "../../../base/logs.h"

void print_ver1()
{
    LOG_FUNC();
    std::cout << "!!!Terminator!!!" << std::endl;
}

template<typename T, typename ... Types>
void print_ver1(T firstArg, Types ... args)
{
    LOG_FUNC();
    std::cout << firstArg << std::endl;
    print_ver1(args ...);
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

// C++17
// terminator function is not required
// based on: fold expressions
template<typename ... Args>
void print_ver3(Args ... args)
{
    LOG_FUNC();
    (std::cout << ... << args);
    // 5. :(  no spaces beween the arguments!
}


// C++17
// terminator function is not required
// - using fold expressions with auto template parameters
// - using ... parameters with comma
template<auto sep = ' ', typename First, typename ... Types>
void print_ver4_COOL(const First& first, const Types ... args)
{
    LOG_FUNC();
    std::cout << first;
    auto outWithSep = [] (const auto& arg) {
        std::cout << sep << arg;

    };
    (..., outWithSep(args));
    std::cout << std::endl;
}

void Test2()
{
    LOG_BEG();
    print_ver1(1, "someString", 2.1);
//OUTPUT:
//    void print_ver1(T, Types ...) [with T = int; Types = {const char*, double}]
//    1
//    void print_ver1(T, Types ...) [with T = const char*; Types = {double}]
//    someString
//    void print_ver1(T, Types ...) [with T = double; Types = {}]
//    2.1
//    void print_ver1()
//    !!!Terminator!!!



    LOG_BR();
    print_ver2(2, "someString2", 3.2);
//OUTPUT:
//    void print_ver2(T, Types ...) [with T = int; Types = {const char*, double}]
//    2
//    void print_ver2(T, Types ...) [with T = const char*; Types = {double}]
//    someString2
//    void print_ver2(T, Types ...) [with T = double; Types = {}]
//    3.2


    LOG_BR();
    print_ver3(3, "someString3", 4.3);
//OUTPUT:
    //   void print_ver3(Args ...) [with Args = {int, const char*, double}]
    //   3someString34.3void <--no separators between arguments

    LOG_BR();
    print_ver4_COOL(4, "someString4", 5.4);
//OUTPUT:
//    void print_ver4_COOL(const First&, const Types ...) [with auto sep = ' '; First = int; Types = {const char*, double}]
//    4 someString4 5.4 <--YES! now there are separators ' ' between the arguments


    LOG_BR();
    std::string s{"someString5"};
    print_ver4_COOL(5, s, 6.5);
//OUTPUT:
//    void print_ver4_COOL(const First&, const Types ...) [with auto sep = ' '; First = int; Types = {std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, double}]
//    5 someString5 6.5


    LOG_BR();
    // non-default separator
    print_ver4_COOL<'#'>(5, s, 6.5);
//OUTPUT:
//    void print_ver4_COOL(const First&, const Types ...) [with auto sep = '#'; First = int; Types = {std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, double}]
//    5#someString5#6.5


    LOG_BR();
    // non-default separator
    // 6. !!! No linkage supported for string literals as template arguments
    static const char sep[] = ", ";
    print_ver4_COOL<sep>(5, s, 6.5);
//OUTPUT:
//    void print_ver4_COOL(const First&, const Types ...) [with auto sep = (& sep); First = int; Types = {std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, double}]
//    5, someString5, 6.5

    LOG_END();
}
