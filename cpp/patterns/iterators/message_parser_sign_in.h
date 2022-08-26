#ifndef MESSAGE_PARSER_SIGN_IN_H_
#define MESSAGE_PARSER_SIGN_IN_H_

#include "message_parser.h"
#include <vector>

#include "./field.hpp"

class MessageParserSignIn : public MessageParser {
 public:
    explicit MessageParserSignIn(TFields && fields);
    virtual void Parse(std::string_view str);
};

#endif  // MESSAGE_PARSER_SIGN_IN_H_
