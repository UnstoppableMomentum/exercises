#ifndef TEST3_H
#define TEST3_H

// C++11
// doing std::move() on an lvalue reference is bad!
// Code producing an lvalue reference expects the object to remain valid.
// But code receiving an rvalue reference expects to be able to steal from it.
// This leaves you with a reference pointing to a potentially-invalid object.
void Test3();

#endif // TEST3_H
