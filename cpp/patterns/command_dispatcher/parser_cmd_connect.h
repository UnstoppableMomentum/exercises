#ifndef PARSER_CMD_CONNECT_H_
#define PARSER_CMD_CONNECT_H_

#include <iostream>
#include <string>
#include <string_view>
#include <tuple>

struct ParserCmdConnect
{
    std::string data_;
    ParserCmdConnect() = delete;
    ParserCmdConnect(std::string_view data)
        : data_(data)
    {
        std::cout << __PRETTY_FUNCTION__ << " data:" << data << std::endl;
    }

    ParserCmdConnect(const ParserCmdConnect &) = delete;

    ParserCmdConnect(const ParserCmdConnect &&parser2)
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }

    ~ParserCmdConnect()
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }

    const ParserCmdConnect &operator=(ParserCmdConnect &&parser)
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        return *this;
    }

    const ParserCmdConnect &operator=(const ParserCmdConnect &parser) = delete;

    bool Validate()
    {
        return true;
    }

    std::tuple<int, std::string> Parse(std::string_view data)
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        std::string s(data);
        return std::make_tuple(1, s);
    }
};

#endif // PARSER_CMD_CONNECT_H_
