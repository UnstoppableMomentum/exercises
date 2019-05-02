#ifndef TEST3_H
#define TEST3_H


// C++11
// Copy constructors can also bind to rvalues (with lower priority).
void Test3();
// Move constructors will only bind to non-const rvalues.
void Test3_1();

#endif // TEST3_H
