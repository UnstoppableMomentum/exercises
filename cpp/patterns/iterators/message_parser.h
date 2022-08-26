#ifndef MESSAGE_PARSER_H_
#define MESSAGE_PARSER_H_

#include <string_view>
#include <vector>

#include "./field.hpp"

typedef std::vector<Field> TFields;

class MessageParser {
    TFields fields_;
public:
    explicit MessageParser(TFields && fields);
    TFields::const_iterator begin() const { return fields_.begin(); }
    TFields::const_iterator end() const { return fields_.end(); }
    virtual void Parse(std::string_view str) = 0;

};

#endif  // MESSAGE_PARSER_H_
