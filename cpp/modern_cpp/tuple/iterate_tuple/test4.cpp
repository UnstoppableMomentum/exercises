#include <tuple>
#include <iostream>

namespace {
template <typename TupleT, std::size_t... Is>
void printTupleImp(const TupleT& tp, std::index_sequence<Is...>) {
    size_t index = 0;
    auto printElem = [&index](const auto& x) {
        if (index++ > 0) 
            std::cout << ", ";
        std::cout << x;
    };

    std::cout << "(";
    (printElem(std::get<Is>(tp)), ...);
    std::cout << ")";
}

template <typename TupleT, std::size_t TupSize = std::tuple_size_v<TupleT>>
void printTuple(const TupleT& tp) {
    printTupleImp(tp, std::make_index_sequence<TupSize>{});
}

}
void test4() {
std::tuple tp { 10, 20, "hello"};
printTuple(tp);
}