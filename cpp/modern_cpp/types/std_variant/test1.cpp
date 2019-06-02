#include "test1.h"
#include "logs.h"

#include <variant>

void Test1() {
    LOG_BEG();
    {
        // variant with 3 alternatives
        std::variant<int, float, std::string>  v;
        // 1. initialize with the first alterative (index()==0)
        std::cout << v.index() << std::endl
                  << " std::get:"<< std::get<0>(v) <<std::endl
                  << " std::get:"<< std::get<int>(v) <<std::endl;
        //OUTPUT:
        //0
        //std::get:0
        //std::get:0
    }

LOG_BR();
    {
        // variant with 3 alternatives
        std::variant<std::string, float, int>  v;
        // 1. initialize with the first alterative
        std::cout << v.index() << std::endl
                  << " std::get:'"<< std::get<0>(v) << "'" << std::endl
                  << " std::get:'"<< std::get<std::string>(v) << "'" << std::endl;
         // 2. RUNTIME ERROR: throw_bad_variant_access
         //   << std::get<int>(v) <<std::endl;

        std::cout << "Change type and index:"<< std::endl;
        v = 0;
        std::cout << v.index() << std::endl;
        v = 0.1f;
        std::cout << v.index() << std::endl;
        v = "qqq";
        std::cout << v.index() << std::endl;
        //OUTPUT:
        //0
        // std::get:''
        // std::get:''
        //Change type and index:
        //2
        //1
        //0
    }

LOG_BR();
    {
        // variant with 3 alternatives
        std::variant<int, float, std::string>  v1{"my string"};

        // 1. s type is std::variant
        auto s = v1;
        std::cout << "s:" << std::get<std::string>(s) << std::endl;

        // 2. Checks if the variant s holds the alternative type:
        std::cout << "s holds_alternative:"
                  << " int:"  << std::holds_alternative<int>(s) << std::endl
                  << " string:" << std::holds_alternative<std::string>(s) << std::endl;

        // 3. holds_alternative(char) fails:
        //    ERROR:  static assertion failed: T should occur for exactly once in alternatives
        //    std::cout << "s holds_alternative:"
        //                  << " char:" << std::holds_alternative<char>(s) << std::endl;

// OUTPUT:
        //s:my string
        //s holds_alternative: int:0
        //string:1
    }
    LOG_END()
}
