#include "test2.h"
#include "logs.h"
#include <memory>

class A {
public:
    A() {
        LOG_FUNC();
    }

    A (const A & c) {
        LOG_FUNC();
    }

    A& operator = (const A & c) {
        LOG_FUNC();
    }
    // !!!
    virtual ~A() {
        LOG_FUNC();
    }

    void doSmth2() const {
        LOG_FUNC();
    }

    virtual void doSmth() & {
        LOG_FUNC();
    }

    virtual void doSmth() && {
        std::cout << __PRETTY_FUNCTION__ <<  std::endl;
    }
};

class B : public A {
public:
    B() {
        LOG_FUNC();
    }

    // 1. virtual destructor is generated automatically
    // ~B() {
    //      LOG_FUNC();
    // }

    B (const B & c) {
        LOG_FUNC();
    }

    B& operator = (const B & c) {
        LOG_FUNC();
    }
    // !!!
    virtual ~B() {
        LOG_FUNC();
    }

    // 2.  error: ‘virtual void B::doSmth2() const’ marked ‘override’, but does not override
    //    without 'override' doSmth2 is compiled OK but it doesn't overload A::doSmth2()
    //    virtual void doSmth2() const override {
    //        LOG_FUNC();
    //    }

    virtual void doSmth() & override {
        LOG_FUNC();
    }

    virtual void doSmth() && override {
        LOG_FUNC();
    }
};

class C : public B {
public:
    C() {
        LOG_FUNC();
    }

    ~C() {
        LOG_FUNC();
    }

    C (const C& c) {
        LOG_FUNC();
    }

    virtual void doSmth() & final {
        LOG_FUNC();
    }

    virtual void doSmth() && override {
        LOG_FUNC();
    }
};

// C+11
class D : public C {
public:

    // 6. error: overriding final function ‘virtual void C::doSmth() &’
    //    virtual void doSmth() & override {
    //        LOG_FUNC();
    //    }

    // 7. OK
    virtual void doSmth() && override {
        LOG_FUNC();
    }
};


// factory function (returns rvalue)
A makeA() {
    LOG_FUNC();
    return A();
}

// C+1 Reference Qualifiers
void Test2()
{
    LOG_BEG();
    // 2. C++14 std::make_unique
    {
        std::unique_ptr<A> pA = std::make_unique<B>();
        pA->doSmth();
    }
    LOG_BR();
    {
        std::unique_ptr<A> pA = std::make_unique<C>();
        // 3. Calls "void C::doSmth() &" version
        pA->doSmth();
    }
    LOG_BR();
    // 4. Calls "void C::doSmth() &" version
    std::make_unique<C>()->doSmth();
    LOG_BR();
    // 5. Calls "void C::doSmth() &&" version
    C().doSmth();
    LOG_END();
}
