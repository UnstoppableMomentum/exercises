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
template <typename... Args>
void printImpl(const Args&... tupleArgs) {
    size_t index = 0;
    auto printElem = [&index](const auto& x) {
        if (index++ > 0) 
            std::cout << ", ";
        std::cout << x;
        };

    (printElem(tupleArgs), ...);
}

template <typename... Args>
void printTupleApplyFn(const std::tuple<Args...>& tp) {
    std::cout << "(";
    std::apply(printImpl<Args...>, tp); // <<
    std::cout << ")";
}

}

void test7(){
    std::tuple tp { 10, 20, 3.14};
    printTupleApplyFn(tp);
}