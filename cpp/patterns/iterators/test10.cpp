// This dosen't work

// candidate template ignored: couldn't infer template argument '_Fn

// template <typename... Args>
// void printImpl(const Args&... tupleArgs) {
//     size_t index = 0;
//     auto printElem = [&index](const auto& x) {
//         if (index++ > 0) 
//             std::cout << ", ";
//         std::cout << x;
//     };

//     (printElem(tupleArgs), ...);
// }

// template <typename... Args>
// void printTupleApplyFn(const std::tuple<Args...>& tp) {
//     std::cout << "(";
//     std::apply(printImpl, tp);
//     std::cout << ")";
// }

/////////////////
#include <iostream>
#include <tuple>

namespace {

template <typename TupleT>
void printTupleApply(const TupleT& tp) {
    //  code breaks when tuple has no elements - we could fix this by checking its size in if constexpr,
    //  but let’s skip it for now.
    std::apply
        (
            [](const auto& first, const auto&... restArgs) {
                auto printElem = [](const auto& x) {
                    std::cout << ", " << x;
                };
                std::cout << "(" << first;
                (printElem(restArgs), ...);
            }, tp);
    std::cout << ")";
}
}

void test10() {
    std::tuple tp { 10, 20, 3.14, 42, "hello"};
    printTupleApply(tp);
}