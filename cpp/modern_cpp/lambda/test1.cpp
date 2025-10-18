/*
* Copyright 2025 <QQQ>
*/

#include "test1.h"

#include <iostream>

// In C++, a stateless lambda function is a lambda expression that does
// not capture any variables from its surrounding scope. This means its capture list [] is empty.


void f(int a = []() { static int b = 1; return b++; }())
{
    std::cout << a;
}

void Test1()
{
    f();
    f();
}