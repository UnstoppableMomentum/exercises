#include <tuple>
#include <iostream>

void test1() {
    std::tuple tp {42, 10.5, "hello"};
  
    // по индексу:
    std::get<0>(tp) *= 100;
    std::cout << std::get<0>(tp) << '\n';
    std::cout << std::get<2>(tp) << '\n';
    
    // по типу:
    std::cout << std::get<double>(tp) << '\n';
}