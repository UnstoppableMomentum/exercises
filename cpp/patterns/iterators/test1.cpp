#include <iterator>
#include <iostream>
#include <algorithm>

#include "message_parser_sign_in.h"

template <class T> class ParserIterator;


template<class T, int N>
class Parser {
    T data[N] = { 0 };
 public:
    ParserIterator<T> begin() {
        return ParserIterator<T>(data);
    }
    ParserIterator<T> end() {
        return ParserIterator<T>(data + N);
    }
};


template <class T>
class ParserIterator
{
public:
    T* data;
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using difference_type = size_t;
    using pointer = T*;
    using reference = T&;

    ParserIterator(){}
    ParserIterator(pointer _data) : data(_data) {}

    reference operator*() { return *data; }
    bool operator!=(const ParserIterator& other)
    {
        return data != other.data;
    }
    ParserIterator<T>& operator++()
    {
        data += 1;
        return *this;
    }
    ParserIterator<T> operator++(int)
    {
        return ParserIterator<T>(data + 1);
    }
};


int test1(void) {

    // TFields fields = {
    //     {EType::eTypeInt, "field0"},
    //     {EType::eTypeFloat, "field1"},
    //     {EType::eTypeString, "field2"}
    // };


    // fields.push_back({EType::eTypeInt, "field0"});
    // fields.push_back({EType::eTypeFloat, "field1"});
    // fields.push_back({EType::edTypeString, "field2"});
    
    // for (auto f : fields) {
    //     std::cout << (int)f.type_ << f.name_ << std::endl;
    // }

    MessageParserSignIn msg({
            {EType::eTypeInt, "field0"},
            {EType::eTypeFloat, "field1"},
            {EType::eTypeString, "field2"}
        });

    for (auto f : msg) {
        std::cout << "q" << (int)f.type_ << f.name_ << std::endl;
    }



    // Parser<int,10> test;

    // std::fill(test.begin(), test.end(), 2);

    // std::transform(test.begin(), test.end(), test.begin(), [](int i)
    // {
    //     return i * i;
    // });

    // for(auto t : test)
    //     std::cout << t << std::endl;

    return 0;
}  