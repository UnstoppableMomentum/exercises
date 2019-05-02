#ifndef TEST1_H
#define TEST1_H

// C++11
// Example of a class with a move constructor.
// It will cause the compiler to not generate an
// implicit copy constructor, making this class move-only.
// Copy constructor is implicitly deleted.
void Test1();
void Test1_1();

#endif // TEST1_H
