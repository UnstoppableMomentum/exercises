#include "./message_parser.h"

MessageParser::MessageParser(TFields &&  fields)
    : fields_(std::move(fields)) {

}