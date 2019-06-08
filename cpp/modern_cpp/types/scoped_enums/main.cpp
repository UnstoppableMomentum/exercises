// Modern C++
// Scoped enums, std::underlying_type_t

#include <tuple>
#include <iostream>
#include <string>

void Test1()
{
    enum oldEnum {one, two, three};

    // 1. compilation error: ‘auto one’ redeclared as different kind of symbol
    //auto one = 1.01;
}

void Test2()
{
    // C++11
    enum class newEnum {one, two, three};

    // 2. OK
    auto one = 1.01;
    std::cout << "one:" << one << std::endl;
}

void Test3()
{
    enum oldEnum {one, two, three};
    oldEnum e = two;

    // 3. OK: compare oldEnum to double
    if(e > 1.01)
    {
        std::cout << "e:" << e << std::endl;
    }
}


void Test4()
{
    // C++11
    enum class newEnum {one, two, three};
    newEnum e = newEnum::two;

    // 4. error: no match for ‘operator>’ (operand types are ‘Test4()::newEnum’ and ‘double’)
    // if(e > 1.01) {}
}

// 5. C++11 forward declaration
// By default, the underlying type for scoped enums is int:
enum class newEnumDef;
enum class newEnum8_t: std::uint8_t;
enum class newEnum16_t: std::uint16_t;
void Test5()
{
    enum class newEnumDef {one, two, three};
    auto e = newEnumDef::two;

    // 6. error: no match for ‘operator<<’ (operand types are ‘std::basic_ostream<char>’ and ‘Test5()::newEnumDef’)
    // std::cout << "e:" << e << std::endl;
    std::cout << "e:" << static_cast<int>(e) << std::endl;

    std::cout << "sizeof(newEnumDef):" << sizeof(newEnumDef) << std::endl;
    std::cout << "sizeof(newEnum8_t):" << sizeof(newEnum8_t) << std::endl;
    std::cout << "sizeof(newEnum16_t):" << sizeof(newEnum16_t) << std::endl;

    // OUTPUT:
    // e:1
    // sizeof(newEnumDef):4
    // sizeof(newEnum8_t):1
    // sizeof(newEnum16_t):2
}

// Test6
// 10. Avoid static_cast.
// Solution#1: C++11
template<typename E>
constexpr typename std::underlying_type<E>::type
toUType(E enumerator) noexcept
{
    return static_cast<typename std::underlying_type<E>::type>(enumerator);
}

// Test6
// 11. Avoid static_cast.
// Solution#2: C++14 std::underlying_type_t
template<typename E>
constexpr /*typename*/std::underlying_type_t<E>/*::type*/
toUType2(E enumerator) noexcept
{
    return static_cast<std::underlying_type_t<E>/*::type*/>(enumerator);
}

// Test6
// 12. Avoid static_cast.
// Solution#3: C++14 auto
template<typename E>
constexpr auto
toUType3(E enumerator) noexcept
{
    return static_cast<std::underlying_type_t<E>>(enumerator);
}

void Test6()
{
    std::cout << __PRETTY_FUNCTION__ << ">>>" << std::endl;
    auto item0 = std::make_tuple("Zero", 0);

    {
        auto strVal0 = std::get<0>(item0);
        std::cout << "strVal0:" << strVal0 << std::endl;
        // OUTPUT:
        //strVal0:Zero
    }

    {
        enum oldEnum {zero, one};
        // 7. OK
        auto strVal0 = std::get<zero>(item0);
        auto strVal1 = std::get<one>(item0);
        std::cout << "strVal0:" << strVal0 << " strVal1:" << strVal1 << std::endl;
        // OUTPUT:
        // strVal0:Zero strVal1:0
    }

    {
        enum class newEnum {zero, one};
        // 8. compilation error
        // auto strVal0 = std::get<newEnum::zero>(item0);

        // 9. OK
        auto strVal0 = std::get<static_cast<size_t>(newEnum::zero)>(item0);
        std::cout << "strVal0:" << strVal0 << std::endl;
        // OUTPUT:
        // strVal0:Zero

        // 10. Avoid static_cast.
        // Solution#1: C++11
        {
            auto strVal0 = std::get<toUType(newEnum::zero)>(item0);
            std::cout << "Solution#1 strVal0:" << strVal0 << std::endl;
            // OUTPUT:
            // Solution#1 strVal0:Zero
        }

        // 11. Avoid static_cast.
        // Solution#2: C++14 std::underlying_type_t
        {
            auto strVal0 = std::get<toUType2(newEnum::zero)>(item0);
            std::cout << "Solution#2 strVal0:" << strVal0 << std::endl;
            // OUTPUT:
            // Solution#2 strVal0:Zero
        }

        // 12. Avoid static_cast.
        // Solution#3: C++14 auto
        {
            auto strVal0 = std::get<toUType3(newEnum::zero)>(item0);
            std::cout << "Solution#3 strVal0:" << strVal0 << std::endl;
            // OUTPUT:
            // Solution#3 strVal0:Zero
        }
    }
    std::cout << __PRETTY_FUNCTION__ << "<<<" << std::endl;
}

int main(int argc, char *argv[])
{
    std::cout << __PRETTY_FUNCTION__ << ">>>" << std::endl;
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
    Test6();
    std::cout << __PRETTY_FUNCTION__ << "<<<" << std::endl;
    return 0;
}
