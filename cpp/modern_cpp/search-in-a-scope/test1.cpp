/*
* Copyright 2025 <QQQ>
*/

#include <iostream>

int foo()
{
  return 10;
}

struct foobar
{
  static int x;
  static int foo()
  {
    return 11;
  }
};

// In the statement int foobar::x = foo();
// we redeclare the variable x.
// Its target scope is a class scope introduced by the declaration of the class foobar 
// (§[dcl.meaning.general]¶3.4). 
// The portion after x is also included in that scope. 
// So when looking for foo we find foobar::foo there and don't search any further
// https://cppquiz.org/quiz/question/126
int foobar::x = foo();

void Test1() {
std::cout << foobar::x;
}
