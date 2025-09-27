/*
* Copyright 2025 <QQQ>
*/

#include "test1.h"

#include <iostream>

void f(int a = []() { static int b = 1; return b++; }())
{
    std::cout << a;
}

void Test1()
{
    f();
    f();
}