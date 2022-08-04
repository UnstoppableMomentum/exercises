#include <tuple>
#include <iostream>

namespace {
template <typename T>
void printElem(const T& x) {
    std::cout << x << ',';
};

template <typename TupleT, std::size_t... Is>
void printTupleManual(const TupleT& tp) {
    (printElem(std::get<Is>(tp)), ...);
}
}
void test3(){
std::tuple tp { 10, 20, "hello"};
printTupleManual<decltype(tp), 0, 1, 2>(tp);
}