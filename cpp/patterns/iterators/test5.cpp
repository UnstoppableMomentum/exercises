#include <iostream>
#include <ostream>
#include <tuple>

namespace {
template <typename TupleT, std::size_t... Is>
std::ostream& printTupleImp(std::ostream& os, const TupleT& tp, std::index_sequence<Is...>) {
    auto printElem = [&os](const auto& x, size_t id) {
        if (id > 0) 
            os << ", ";
        os << id << ": " << x;
    };

    os << "(";
    (printElem(std::get<Is>(tp), Is), ...);
    os << ")";
    return os;
}

template <typename TupleT, std::size_t TupSize = std::tuple_size<TupleT>::value>
std::ostream& operator <<(std::ostream& os, const TupleT& tp) {
    return printTupleImp(os, tp, std::make_index_sequence<TupSize>{}); 
}

}
void test5() {
    std::tuple tp { 10, 20, "hello"};
    std::cout << tp << '\n';
}