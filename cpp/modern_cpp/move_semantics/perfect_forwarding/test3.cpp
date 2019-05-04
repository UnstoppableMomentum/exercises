#include "test3.h"
#include "../../../../base/logs.h"

class MyType {
 public:
  MyType() {
    pointer = new int;
    *pointer = 42;
  }
  MyType(MyType&& other) {
    pointer = other.pointer;
    other.pointer = nullptr;
  }
  ~MyType() {
    delete pointer;
  }

  int* pointer;
};

void Oops(MyType& type) {
  // 1. Move is destructive. It can change |type| which is an lvalue reference.
  MyType local_type = std::move(type);

  // Work with local_type.
  // ...
}

void Test3()
{
  MyType type;
  // Don't move type, just pass it.
  Oops(type);
  // 2. Error: now type.pointer == nullptr
  *type.pointer = 314;
}
