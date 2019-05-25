#include "test1.h"
#include "logs.h"


#include <iostream>

// C98
// Disable functions using visibility
class OldStyleClass {
public:
    OldStyleClass() {}
private:
    OldStyleClass(const OldStyleClass&);
    OldStyleClass& operator = (const OldStyleClass&);
};

// C++11
// Disable member functions using "=delete"
class NewStyleClass {
public:
    NewStyleClass() {}
    //private:
    NewStyleClass(const NewStyleClass&) = delete;
    NewStyleClass& operator = (const NewStyleClass&) = delete;
};




// C++11
// Disable non-member function using "=delete"
void NonMember(int i) {
    std::cout << "qqq(int) i:" << i << std::endl;
}
void NonMember(double i) = delete;



class MyClass {
public:
    template<typename T>
    void qqq(T t) {
        std::cout << "MyClassqqq(T) t:" << t << std::endl;
    }
// compile error: explicit specialization in non-namespace scope ‘class MyClass’ template<>
//            error: template-id ‘qqq<double>’ in declaration of primary template
//            error: ‘void MyClass::qqq(double)’ is private
// private:
//    template<>
//    void qqq <double> (double d) {
//        std::cout << "MyClassqqq(double) d:" << d << std::endl;
//    }
};

template<>
void MyClass::qqq <double> (double v) {
    std::cout << "MyClassqqq(double) v:" << v << std::endl;
}

// C++11
template<>
void MyClass::qqq <bool> (bool v) = delete;

void Test1()
{
    std::cout << ">>>" << std::endl;
    OldStyleClass oldStyleClass;

    // 1. compilation error: ‘OldStyleClass::OldStyleClass(const OldStyleClass&)’ is PRIVATE
    // OldStyleClass oldStyleClass1(oldStyleClass);

    OldStyleClass oldStyleClass2;
    // 2. compilation error: ‘OldStyleClass& OldStyleClass::operator=(const OldStyleClass&)’ is PRIVATE
    // oldStyleClass2 = oldStyleClass;

    // 3. compilation error: ‘OldStyleClass::OldStyleClass(const OldStyleClass&)’ is PRIVATE
    //OldStyleClass oldStyleClass3 = oldStyleClass;

    NewStyleClass newStyleClass;
    // 4. compilation error: use of DELETED function ‘NewStyleClass::NewStyleClass(const NewStyleClass&)’
    //NewStyleClass newStyleClass1(newStyleClass);

    NewStyleClass newStyleClass2;
    // 5. compilation error: use of DELETED function ‘NewStyleClass& NewStyleClass::operator=(const NewStyleClass&)’
    //newStyleClass2 = newStyleClass;

    // 6. compilation error: use of DELETED function ‘NewStyleClass::NewStyleClass(const NewStyleClass&)’
    //NewStyleClass newStyleClass3(newStyleClass);

    NonMember(1);
    // 7. compilation error: use of DELETED function ‘void NonMember(double)’
    // NonMember(1.0);

    MyClass myClass;
    myClass.qqq(1);
    myClass.qqq(1.01);

    // 8. error: use of deleted function ‘void MyClass::qqq(T) [with T = bool]’
    //myClass.qqq(true);

    std::cout << "<<<" << std::endl;

}
