/*
* Copyright 2021 <QQQ>
*/

#include <iostream>
#include <string>
#include <string_view>
#include <sstream>

#include "./test2.h"
#include "../../../base/logs.h"

namespace {


class B {
 public:
  typedef int TData;
    void doWork(TData& data) {
    LOG_DBG("data:%d", data);
    }
  bool validate() { return true; }
};


class C {
 public:
  class CommandData {
   public:
    int res;
    std::string err;
    std::string cmd;
  };

  typedef CommandData TData;
    void doWork(TData& data) {
     LOG_DBG("data:%s", data.cmd.c_str());
     data.res = 123;
    }
  bool validate() { return true; }
};

template <typename T>
class A {
  T worker;
 public:
  bool dispatch(typename T::TData& data) {
    bool res = false;
    if (worker.validate()) {
      worker.doWork(data);
      res = true;
    }
    return res;
  }
};

}  // namespace

void Test2() {
  {
    A<B> ab;
    int data = 123;
    bool res = ab.dispatch(data);
    LOG_DBG("AB dispatch result: %d", res);
  }
  {
    A<C> ac;
    C::TData data{0, "", "command1"};
    bool res = ac.dispatch(data);
    LOG_DBG("AC dispatch result: %d", data.res);
  }


}
