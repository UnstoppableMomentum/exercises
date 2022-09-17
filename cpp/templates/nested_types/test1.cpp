/*
* Copyright 2021 <QQQ>
*/

#include <iostream>
#include <string>
#include <string_view>
#include <sstream>

#include "test1.h"
#include "../../../base/logs.h"

namespace {
class B {
 public:
  typedef int retTypeDoWork;
    retTypeDoWork doWork() {
     LOG_FUNC();
     return 123;
    }
};

class C {
 public:
  typedef std::string retTypeDoWork;
    retTypeDoWork doWork() {
     LOG_FUNC();
     return "String result";
    }
};

template <typename T>
class A {
 public:
  typename T::retTypeDoWork a(T t) {
    return t.doWork();
  }
};

}  // namespace

void Test1() {
  // Integer return type
  A<B> ab;
  LOG_DBG("Nested type int: %d", ab.a(B()));

  // String return type
  A<C> ac;
  LOG_DBG("Nested type string: %s", ac.a(C()).c_str());
}
