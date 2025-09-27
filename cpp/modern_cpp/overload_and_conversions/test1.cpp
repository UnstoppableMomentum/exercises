/*
* Copyright 2025 <QQQ>
*/


#include "test1.h"
#include <iostream>

void f(int) { std::cout << 1; }
void f(unsigned) { std::cout << 2; }
// compilation error : call of overloaded ‘f(double)’ is ambiguous

// NOTE: conversion double -> int is OK

void Test1() {
  f(-2.5);
}
