#ifndef STACK_COMMON_H
#define STACK_COMMON_H

#include <exception>

struct EmptyStackException: std::exception
{
    const char* what() const throw()
    {
        return "stack is empty";
    }
};

#endif // STACK_COMMON_H
