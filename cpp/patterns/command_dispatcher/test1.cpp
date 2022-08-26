#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <string_view>
#include <tuple>

#include "parser_cmd_connect.h"
#include "parser_cmd_send_message.h"

void sendMessage(int32_t param0, std::string str, std::string str2)
{
    std::cout << "DISPATCH " << __FUNCTION__ << " " << param0 << " str:" << str << " str2:" << str2 << std::endl;
}

void func1(int32_t param0, std::string str)
{
    std::cout << "DISPATCH " << __FUNCTION__ << " " << param0 << " str:" << str << std::endl;
}

template <typename TParser, typename... Args>
struct tuple_reader_sv {
    static std::tuple<> read(std::string_view, TParser &&parser) {
        return {};
    }
};

template <typename TParser, typename First, typename... Rest>
struct tuple_reader_sv<TParser, First, Rest...> {
    static std::tuple<First, Rest...> read(std::string_view packet, TParser &&parser) {
        return parser.Parse(packet);
    }
};

class Dispatcher {
    std::map<uint32_t, std::function<void(std::string_view)>> commandMap;

 public:
    template <typename TParser, typename... Args>
    void AddHandler_sv(uint32_t command, void (*func)(Args...)) {
        commandMap.emplace(command, [func](std::string_view data) {
                               std::cout << __PRETTY_FUNCTION__ << std::endl;
                               TParser parser(data);
                               if (parser.Validate()) {
                                   auto args = tuple_reader_sv<TParser, Args...>::read(data, std::move(parser));
                                   std::apply(func, std::move(args));
                               } else {
                                   std::cout << " invalid data:" << data << std::endl;
                               }
                           });
    }

    void DispatchCommand_sv(uint32_t command, std::string_view data) {
        auto it = commandMap.find(command);
        if (it != commandMap.end()) {
            it->second(data);
        } else {
            std::cout << "command :" << command << " was not registered" << std::endl;
        }
    }
};

void Test1() {
    Dispatcher d;
    d.AddHandler_sv<ParserCmdConnect>(6, func1);
    d.AddHandler_sv<ParserCmdSendMessage>(1, sendMessage);

    d.DispatchCommand_sv(6, "CONNECT");
    d.DispatchCommand_sv(1, "SEND MESSAGE");
}
