#include "cmd_line.h"
#include "test1.h"

// These tests are based on examples from this book:
// C++ Concurrency in action by Anthony Williams
//
//
// Test description:
// During the test several threads read and remove the top item from
// the same data stack. Each item read is placed in an array of results.
// When all data is read (the stack is empty), the threads stop.
// At final step the result array is checked for missing and duplicate values.
//
// Test1 demonstrates the data races problem happens as a consequence
// of the design of the interface (see StackBadDesign in stack_data_races.h).
// See explanation in DataRacesTestFunctor::operator()
// The solution is to change the stack interface:
// OPTION 1: PASS IN A REFERENCE TO Pop()
// OPTION 2: REQUIRE A NO - THROW COPY CONSTRUCTOR OR MOVE CONSTRUCTOR
// OPTION 3: RETURN A POINTER TO THE POPPED ITEM
// OPTION 4: PROVIDE BOTH OPTION 1 AND EITHER OPTION 2 OR 3
//
// To avoid data races StackThreadSafeImpl1 (see stack_impl1.h) implements
// OPTION 1 (command line parameter "-t2") and
// OPTION 3 (command line parameter "-t1")
//
//
//
// Command line examples:
//
// 1.
// ./data_races_example -n1000
// - Test type: 0 (by default). This demonstrates the data races problem
// - Number of data items: 1000
// - Number of threads: 4 (by default)
//
// Try this test several times,
// Sometimes the results are different due to data races.
//
// 2.
// ./data_races_example -t1 -n1000 -s10
// - Test type: 1. Thread safe stack, implementation 1, use Pop() return shared_ptr
// - Number of data items: 1000
// - Number of threads: 10
//
// 3.
// ./data_races_example -t2 -n1000 -s10
// - Test type: 1. Thread safe stack, implementation 1, use Pop(T&value)
// - Number of data items: 1000
// - Number of threads: 10
//
// See cmd_line.cpp for command line options description

int main(int argc, char *argv[])
{
    TestOptions testOptions;
    bool bRes = parseCommandLine(testOptions, true, argc, argv);
    if (bRes) {
        Test1(testOptions);
    }
    return 0;
}

