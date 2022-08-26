#ifndef MESSAGE_H_
#define  MESSAGE_H_

#include <vector>

#include "./field.hpp"

typedef std::vector<Field> TFields;

class Message {
    TFields fields_;
 public:
    explicit Message(TFields && fields);
    TFields::const_iterator begin() const { return fields_.begin(); }
    TFields::const_iterator end() const { return fields_.end(); }
};

#endif  //  MESSAGE_H_
