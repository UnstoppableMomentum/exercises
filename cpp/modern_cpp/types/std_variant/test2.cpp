#include "test2.h"
#include "logs.h"

#include <variant>
#include <vector>

class A
{
public:
    void DoWork()const
    {
        std::cout << "A";
    }
};

class B
{
public:
    void DoWork() const
    {
        std::cout << "B";
    }
};

using var_object = std::variant<A,B>;

std::vector<var_object>CreateVarObjects()
{
    std::vector<var_object> res;
    res.push_back(A());
    res.push_back(B());
    res.push_back(B());
    res.push_back(A());
    return res;
}

void DoWork(const std::vector<var_object>& v)
{
    for(const auto& obj : v) {
        std::visit ([] (const auto& obj) {
            // polimorphic call
            // visitor uses a local variable
            obj.DoWork();
        },
        obj);
    }
    std::cout << std::endl;
}

void Test2()
{
    LOG_BEG();
    std::vector<var_object> var_objects = CreateVarObjects();
    DoWork(var_objects);
// OUTPUT:
//    ABBA
    LOG_END();
}
