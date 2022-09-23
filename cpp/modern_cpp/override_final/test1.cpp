#include "test1.h"
#include "logs.h"

// Reference Qualifiers
// A non-static member function can be declared with:
//  - no ref-qualifier, with an lvalue ref-qualifier (the token & after the parameter list)
//  - or the rvalue ref-qualifier (the token && after the parameter list).
// During overload resolution, non-static cv-qualified member function of class X is treated as follows:
// 1. no ref-qualifier    : the implicit object parameter has type lvalue reference to cv-qualified X
//                            and is additionally allowed to bind rvalue implied object argument
// 2. lvalue ref-qualifier: the implicit object parameter has type lvalue reference to cv-qualified X
// 3. rvalue ref-qualifier: the implicit object parameter has type rvalue reference to cv-qualified X
class ClassWithRefQual {
public:

    ClassWithRefQual() {
        LOG_FUNC();
    }

    ClassWithRefQual (const ClassWithRefQual & c) {
        LOG_FUNC();
    }

    ClassWithRefQual& operator = (const ClassWithRefQual & c) {
:        LOG_FUNC();
    }

    // 1. reference qualifier, applies only when *this is an lvalue
    void doSmth() & {
        LOG_FUNC();
    }

    // 2. error: ‘void ClassWithRefQual::doSmth()’ cannot be overloaded
    // 3. error: ‘void ClassWithRefQual::doSmth() &&’ cannot be overloaded
    // void doSmth() {
    //   LOG_FUNC();
    // }

    // 4. reference qualifier, applies only when *this is an rvalue
    void doSmth() && {
        std::cout << __PRETTY_FUNCTION__ <<  std::endl;
    }

    // 5. accepts only lvalue parameter
    // 6. Same as above: needs reference qualifier when "*this rvalue"
    // version is defined : "doSmth(ClassWithRefQual& v) &&"
    // error: ‘void ClassWithRefQual::doSmth(ClassWithRefQual&) &&’ cannot be overloaded"
    // void doSmth(ClassWithRefQual& v) {
    //    LOG_FUNC();
    // }

    // 7. accepts only rvalue parameter
    void doSmth(ClassWithRefQual& v) & {
        LOG_FUNC();
    }

    // 8. accepts only rvalue parameter
    void doSmth(ClassWithRefQual&& v) & {
        LOG_FUNC();
    }

    // 9. accepts only lvalue parameter
    //  reference qualifier, applies only when *this is an rvalue
    void doSmth(ClassWithRefQual& v) && {
        LOG_FUNC();
    }

    // 10. accepts only rvalue parameter
    //  reference qualifier, applies only when *this is an rvalue
    void doSmth(ClassWithRefQual&& v) && {
        LOG_FUNC();
    }
};


// factory function (returns rvalue)
ClassWithRefQual makeClassWithRefQual() {
    LOG_FUNC();
    return ClassWithRefQual();
}

// C+11 Reference Qualifiers
void Test1()
{
    LOG_BEG();
    // normal object (an lvalue)
    ClassWithRefQual crq;
    // 5. error: with only "void doSmth() && " version leads to this error:
    // passing ‘ClassWithRefQual’ as ‘this’ argument discards qualifiers [-fpermissive]
    crq.doSmth();

    // call rvalule version
    makeClassWithRefQual().doSmth();

    // OUTPUT:
    //    ClassWithRefQual::ClassWithRefQual()
    //    void ClassWithRefQual::doSmth() &
    //    ClassWithRefQual makeClassWithRefQual()
    //    ClassWithRefQual::ClassWithRefQual()
    //    void ClassWithRefQual::doSmth() &&
    LOG_END();
}

// C+11 rvalue arguments
void Test1_1()
{
    LOG_BEG();
    // normal object (an lvalue)
    // call lvalue version
    {
        ClassWithRefQual crq;
        ClassWithRefQual crq2;
        crq.doSmth(crq2);
    }
    LOG_BR();
    // normal object (an lvalue)
    // call rvalule version
    {
        ClassWithRefQual crq;
        crq.doSmth(makeClassWithRefQual());
        // the same behavior: crq.doSmth(ClassWithRefQual());
    }
    LOG_BR();
    // rvalule
    // call lvalule version
    {
        ClassWithRefQual crq2;
        ClassWithRefQual().doSmth(crq2);
    }
    LOG_BR();
    // rvalule
    // call rvalule version
    {
        ClassWithRefQual().doSmth(ClassWithRefQual());
    }
    LOG_END();
    // OUTPUT:
    //    ClassWithRefQual::ClassWithRefQual()
    //    ClassWithRefQual::ClassWithRefQual()
    //    void ClassWithRefQual::doSmth(ClassWithRefQual&) &
    //    ----------------
    //    ClassWithRefQual::ClassWithRefQual()
    //    ClassWithRefQual makeClassWithRefQual()
    //    ClassWithRefQual::ClassWithRefQual()
    //    void ClassWithRefQual::doSmth(ClassWithRefQual&&) &
    //    ----------------
    //    ClassWithRefQual::ClassWithRefQual()
    //    ClassWithRefQual::ClassWithRefQual()
    //    void ClassWithRefQual::doSmth(ClassWithRefQual&) &&
    //    ----------------
    //    ClassWithRefQual::ClassWithRefQual()
    //    ClassWithRefQual::ClassWithRefQual()
    //    void ClassWithRefQual::doSmth(ClassWithRefQual&&) &&

}
