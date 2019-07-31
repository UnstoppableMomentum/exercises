#include "move_only_class.h"

#include "../../../../base/logs.h"

namespace cpp_exercises {

static int glCounter = 0;

MoveOnlyClass::MoveOnlyClass()
    : id(glCounter++)
    , pointer(new int)
{
    *pointer = id;
    LOG_DBG("id: %d %p %d", id, pointer, *pointer);
}

MoveOnlyClass::~MoveOnlyClass()
{
    LOG_DBG(">>> id: %d %p %d", id, pointer, (pointer ? *pointer : 0));
    if (pointer != nullptr) {
        delete pointer;
        pointer = nullptr;
    }
    LOG_END();
}

MoveOnlyClass::MoveOnlyClass(MoveOnlyClass&& other)
    :id(glCounter++)
    // 1. move semantics, no allocation
    , pointer(nullptr)
{
    LOG_BEG();
    // Note that although the type of |other| is an rvalue reference, |other|
    // itself is an lvalue, since it is a named object. In order to ensure that
    // the move assignment is used, we have to explicitly specify
    // std::move(other).
    *this = std::move(other);
    LOG_DBG("id: %d %p %d", id, pointer, *pointer);
    LOG_END();
}

MoveOnlyClass& MoveOnlyClass::operator = (MoveOnlyClass&& other)
{
    LOG_BEG();
    // 2. !!!
    delete pointer;
    // 3. Steal the memory, null out |other|.
    pointer = other.pointer;
    other.pointer = nullptr;
    LOG_DBG("id: %d %p %d", id, pointer, *pointer);
    // 4. swap, memset, etc inner data
    // ...

    // 5. return
    LOG_END();
    return *this;
}

double MoveOnlyClass::operator() (double d)
{
    LOG_BEG();
    LOG_DBG("000 id: %d %p %d m_d:%4.2f", id, pointer, *pointer, m_d);
    m_d = d;
    LOG_DBG("001 id: %d %p %d m_d:%4.2f", id, pointer, *pointer, m_d);
    LOG_END();
    return static_cast<double>(id);
}

move_only::move_only()
{

}

move_only::move_only(move_only&&)
{
}

move_only& move_only::operator=(move_only&&)
{
    return *this;
}

void move_only::operator()()
{
}

} // namespace cpp_exercises
