
#include <boost/smart_ptr.hpp>

#include <iostream>

struct A {
  virtual ~A() {
     std::cout << __PRETTY_FUNCTION__ << std::endl;
  }
  virtual void f()
   {
     std::cout << __PRETTY_FUNCTION__ << std::endl;
  }
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
  boost::shared_ptr<A> shared_ptr_A_;
  explicit User(boost::shared_ptr<A> shared_ptr_A)
   : shared_ptr_A_(shared_ptr_A)
   {
   }
   void CallF() {
      shared_ptr_A_->f();
   }      
};
 
void test1() {
   User user(boost::make_shared<B>());
   user.CallF();
}  