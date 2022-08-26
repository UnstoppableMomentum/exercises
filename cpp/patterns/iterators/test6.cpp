#include <iostream>
#include <tuple>
 
int sum(int a, int b, int c) { 
    return a + b + c; 
}

void print(std::string_view a, std::string_view b) {
    std::cout << "(" << a << ", " << b << ")\n";
} 

void test6() {
    std::tuple numbers {1, 2, 3};
    std::cout << std::apply(sum, numbers) << '\n';

    std::tuple strs {"Hello", "World"};
    std::apply(print, strs);
}