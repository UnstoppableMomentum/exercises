#ifndef STACK_IMPL1_H
#define STACK_IMPL1_H

#include <mutex>
#include <stack>

#include "stack_common.h"
// TODO
template <typename T>
class StackImpl1
{
public:

    bool Empty() const
    {
        std::lock_guard<std::mutex> lock(m_);
        return data_.empty();
    }

    void Push(T val) {
        std::lock_guard<std::mutex> lock(m_);
        data_.push(val);
    }

    T Top() {
        std::lock_guard<std::mutex> lock(m_);
        if (data_.empty()) {
            throw EmptyStackException();
        }
        return data_.top();
    }

    void Pop() {
        std::lock_guard<std::mutex> lock(m_);
        if (data_.empty()) {
            throw EmptyStackException();
        }
        data_.pop();
    }

private:
    std::stack<T> data_;
    mutable std::mutex m_;
};

#endif // STACK_IMPL1_H
