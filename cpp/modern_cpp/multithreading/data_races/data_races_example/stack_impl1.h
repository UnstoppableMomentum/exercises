#ifndef STACK_IMPL1_H
#define STACK_IMPL1_H

#include <memory>
#include <mutex>
#include <stack>

#include "logs.h"
#include "stack_common.h"

// class StackThreadSafeImpl1
// Thread safe stack implementation N1
template <typename T>
class StackThreadSafeImpl1
{
public:
    StackThreadSafeImpl1()
    {
        LOG_FUNC()
    }

    ~StackThreadSafeImpl1()
    {
        LOG_FUNC()
    }

    StackThreadSafeImpl1& operator=(const StackThreadSafeImpl1&) = delete;

    bool Empty() const
    {
        std::lock_guard<std::mutex> lock(m_);
        return data_.empty();
    }

    void Push(T val) {
        std::lock_guard<std::mutex> lock(m_);
        data_.push(val);
    }

    void Pop(T& value) {
        std::lock_guard<std::mutex> lock(m_);
        if (data_.empty()) {
            throw EmptyStackException();
        }
        value=data_.top();
        data_.pop();
    }

    std::shared_ptr<T> Pop()
    {
        std::lock_guard<std::mutex> lock(m_);
        if(data_.empty()) {
            throw EmptyStackException();
        }
        std::shared_ptr<T> const res(std::make_shared<T>(data_.top()));
        data_.pop();
        return res;
    }

private:
    std::stack<T> data_;
    mutable std::mutex m_;
};

#endif // STACK_IMPL1_H
