#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <tuple>


class Packet {
 public:
    int32_t ReadInt32() { return 1; }
    uint32_t ReadUInt32() { return 2; }
    int8_t ReadInt8() {return 3; }
    std::string ReadString() { return "qqq"; }
};

template<typename T> T Read(Packet& packet) = delete;

template<> int32_t Read<int32_t>(Packet& packet)
    { return packet.ReadInt32(); }

template<> uint32_t Read<uint32_t>(Packet& packet)
    { return packet.ReadUInt32(); }

template<> int8_t Read<int8_t>(Packet& packet)
    { return packet.ReadInt8(); }

template<> std::string Read<std::string>(Packet& packet)
    { return packet.ReadString(); }

void func1(int32_t param0) {
    std::cout << __FUNCTION__ << " " << param0 << std::endl;
}

void func2(int32_t param0, int32_t param1) {
    std::cout << __FUNCTION__ << " " << param0 << ", " << param1 << std::endl;
}

void func3(int32_t param0, int32_t param1, int32_t param2) {
    std::cout << __FUNCTION__ << " " << param0 << ", " << param1 << ", " << param2 << std::endl;
}

void func4(int32_t param0, int32_t param1, int32_t param2, std::string param3) {
    std::cout << __FUNCTION__ << " " << param0 << ", " << param1 << ", " << param2  << ", " << param3 << std::endl;
}


// Q.1 cannon compile template function
// template<typename First, typename... Rest>
// std::tuple<First, Rest...> read_tuple(Packet& packet) {
//   auto first = std::make_tuple(Read<First>(packet));
//   return std::tuple_cat(first, read_tuple<Rest>(packet));
// }

// std::tuple<> read_tuple(Packet& packet) {
//   return std::tuple<>();
// }


template<typename... Args>
struct tuple_reader {
  static std::tuple<> read(Packet&) { return {}; }
};

template<typename First, typename... Rest>
struct tuple_reader<First, Rest...> {
  static std::tuple<First, Rest...> read(Packet& packet) {
    auto first = std::make_tuple(Read<First>(packet));
    return std::tuple_cat(std::move(first), // moved
                 tuple_reader<Rest...>::read(packet));
  }
};


class Dispatcher {
    std::map<uint32_t, std::function<void(Packet&)>> commandMap;

 public:
    void AddHandler(uint32_t command, void (*func)(int32_t, int32_t)) {
        commandMap.emplace(command, [func](Packet& packet) {
            auto param1 = packet.ReadInt32();
            auto param2 = packet.ReadInt32();
            func(param1, param2);
         });
    }

    template <typename... Args>
    void AddHandler2(uint32_t command, void(*func)(Args...)) {
        commandMap.emplace(command, [func](Packet& packet) {
            auto args = std::make_tuple(Read<Args>(packet)...);
            std::apply(func, args);
        });
    }

    // Q.1 cannon compile template function read_tuple
    // template <typename... Args>
    // void AddHandler3(uint32_t command, void(*func)(Args...)) {
    //     commandMap.emplace(command, [func](Packet& packet) {
    //         auto args = read_tuple(packet);
    //         std::apply(func, args);
    //     };
    // }

    template <typename... Args>
    void AddHandler4(uint32_t command, void(*func)(Args...)) {
    commandMap.emplace(command, [func](Packet& packet) {
            auto args = tuple_reader<Args...>::read(packet);
            std::apply(func, std::move(args));   // moved
        });
    }

    void DispatchCommand(uint32_t command, Packet packet) {
        auto it = commandMap.find(command);
        if (it != commandMap.end()) {
            std::cout << "command :" << command << " handled" << std::endl;
           it->second(packet);
        } else {
            std::cout << "command :" << command << " was not registered" << std::endl;
        }
    }
};


int main() {
    Dispatcher d;
    d.AddHandler(1, func2);
    d.AddHandler2(0, func1);
    d.AddHandler2(2, func3);
    d.AddHandler4(4, func4);


    d.DispatchCommand(0, Packet());
    d.DispatchCommand(1, Packet());
    d.DispatchCommand(2, Packet());
    d.DispatchCommand(4, Packet());
    return 0;
}