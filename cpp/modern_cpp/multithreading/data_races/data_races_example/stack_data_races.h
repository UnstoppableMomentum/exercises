#ifndef STACK_DATA_RACES_H
#define STACK_DATA_RACES_H

#include "stack_common.h"

#include <mutex>
#include <stack>

#include "logs.h"

template <typename T>
class StackBadDesign
{
public:

    StackBadDesign()
    {
        LOG_FUNC()
    }

    ~StackBadDesign()
    {
        LOG_FUNC()
    }

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

#endif // STACK_DATA_RACES_H
