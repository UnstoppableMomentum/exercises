#include <iostream>
#include <memory>

struct A {
  virtual ~A() {
     std::cout << __PRETTY_FUNCTION__ << std::endl;
  }
  virtual void f() = 0;
};

struct B : public A {
  virtual ~B() {
      std::cout << __PRETTY_FUNCTION__ << std::endl;
  }
  virtual void f() {
      std::cout << __PRETTY_FUNCTION__ << std::endl;
  }
};

struct User {
  std::shared_ptr<A> shared_ptr_A_;
  explicit User(std::shared_ptr<A> shared_ptr_A)
   : shared_ptr_A_(shared_ptr_A)
   {
   }
   void CallF() {
      shared_ptr_A_->f();
   }      
};
 
void test1() {
   //B b;
   std::shared_ptr<A> pA(new B);
   pA->f();
   //User user(std::make_shared<A>(new B()));
   //user.CallF();
}  