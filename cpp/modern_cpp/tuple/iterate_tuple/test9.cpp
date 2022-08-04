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
    std::cout << "(";
    std::apply([](const auto&... tupleArgs) {
                size_t index = 0;
                auto printElem = [&index](const auto& x) {
                    if (index++ > 0)
                        std::cout << ", ";
                    std::cout << x;
                };

                (printElem(tupleArgs), ...);
            }, tp);
    std::cout << ")";
}

}

void test9() {
    std::tuple tp { 10, 20, 3.14, 42, "hello"};
    printTupleApply(tp);
}
