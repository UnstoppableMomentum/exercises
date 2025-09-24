/*
 * Copyright 2025 qqq
 */

#include "test1.h"

#include <iostream>

struct S
{
  int one;
  int two;
  int three;
};

void testInit()
{
  std::cout << __func__ << std::endl;
  S s{1, 2};
  std::cout << " s.one: " << s.one << " s.two: " << s.two << " s.three: " << s.three << std::endl;
  // OUTPUT:
  // s.one: 1 s.two: 2 s.three: 0
}

void testInit1()
{
  std::cout << __func__ << std::endl;
  S s{};
  std::cout << " s.one: " << s.one << " s.two: " << s.two << " s.three: " << s.three << std::endl;
  // OUTPUT:
  //  s.one: 0 s.two: 0 s.three: 0
}

void testInit2()
{
  std::cout << __func__ << std::endl;
  S s;
  std::cout << " s.one: " << s.one << " s.two: " << s.two << " s.three: " << s.three << std::endl;
  // OUTPUT:
  //  s.one: 0 s.two: 0 s.three: 0
}

void Test1()
{
  testInit();
  testInit1();
  testInit2();
}
