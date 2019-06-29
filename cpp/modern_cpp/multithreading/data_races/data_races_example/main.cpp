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
//
// Command line examples:
//
// ./data_races_example -n1000
// - Test type: 0 (by default). This demonstrates the data races problem
// - Number of data items: 1000
// - Number of threads: 4 (by default)
//
// Try this test several times,
// Sometimes the results are different due to data races.

int main(int argc, char *argv[])
{
    TestOptions testOptions;
    bool bRes = parseCommandLine(testOptions, true, argc, argv);
    if (bRes) {
        Test1(testOptions);
    }
    return 0;
}

