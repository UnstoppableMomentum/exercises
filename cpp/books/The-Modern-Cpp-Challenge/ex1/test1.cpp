#include "test1.h"
#include "logs.h"

#include <chrono>
#include <future>
#include <thread>
#include <functional>

namespace {

// Original code
void Example0(unsigned int limit)
{
    LOG_BEG();

    //unsigned int limit = 0;
    //std::cout << "Upper limit:";

    //std::cin >> limit;

    unsigned long long sum = 0;
    for (unsigned int i = 3; i < limit; ++i)
    {
        if (i % 3 == 0 || i % 5 == 0)
            sum += i;
    }

    std::cout << "sum:" << sum << std::endl;


    LOG_END();
}

// Arithmetic progression
template <typename T>
T SumAP(T first, T last, T step) {
    T num_elements = (last - first) / step;
    T last_correted = first + num_elements * step;
    return (first + last_correted) /2 * num_elements;
}


void Example1(unsigned int limit)
{
    LOG_BEG();
    // Arithmetic progression
    unsigned int sum = SumAP<unsigned int>(0, limit, 3) + SumAP<unsigned int>(0, limit, 5);
    std::cout << "sum:" << sum << std::endl;
    LOG_END();
}

} // namespace

void Test1() {
    LOG_BEG();
    Example0(100);
    Example1(100);
    LOG_END();
}

// Output
//void Test1()>>>
//void {anonymous}::Example0(unsigned int)>>>
// sum:2318
//void {anonymous}::Example0(unsigned int)<<<
//void {anonymous}::Example1(unsigned int)>>>
// sum:2617 <-- different because numbers with a common divisor were summed twice
//void {anonymous}::Example1(unsigned int)<<<
//void Test1()<<<

