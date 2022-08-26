#ifndef PARSER_CMD_SEND_MESSAGE_H_
#define PARSER_CMD_SEND_MESSAGE_H_

#include <iostream>
#include <string>
#include <string_view>
#include <tuple>

struct ParserCmdSendMessage
{
    std::string data_;
    ParserCmdSendMessage() = delete;
    ParserCmdSendMessage(std::string_view data)
        : data_(data)
    {
        std::cout << __PRETTY_FUNCTION__ << " data:" << data << std::endl;
    }

    ParserCmdSendMessage(const ParserCmdSendMessage &) = delete;

    ParserCmdSendMessage(const ParserCmdSendMessage &&parser2)
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }

    ~ParserCmdSendMessage()
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }

    const ParserCmdSendMessage &operator=(ParserCmdSendMessage &&parser)
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        return *this;
    }

    const ParserCmdSendMessage &operator=(const ParserCmdSendMessage &parser) = delete;

    bool Validate()
    {
        return true;
    }

    std::tuple<int, std::string, std::string> Parse(std::string_view data)
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        std::string s(data);
        std::string s2(data);
        return std::make_tuple(1, s, s2);
    }
};

#endif // PARSER_CMD_SEND_MESSAGE_H_
