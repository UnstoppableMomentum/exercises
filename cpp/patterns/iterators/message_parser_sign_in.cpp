#include "./message_parser_sign_in.h"

MessageParserSignIn::MessageParserSignIn(TFields &&  fields)
    : MessageParser(std::move(fields)) {
}

void MessageParserSignIn::Parse(std::string_view str) {

}