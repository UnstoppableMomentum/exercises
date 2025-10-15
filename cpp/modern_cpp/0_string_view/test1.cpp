/*
* Copyright 2021 <QQQ>
*/

#include <string>
#include <string_view>
#include <sstream>

#include "test1.h"
#include "../../../base/logs.h"

class StringOwner {
    std::string m_str;

 public:
    explicit StringOwner(const char * pStr)
    : m_str(pStr) {
         LOG_DBG("pStr: %s", pStr);
    }

    std::string_view GetString() const {
        // !!!ERROR!!!
        // std::substr is an temporary object
        // return m_str.substr(1u);

        // !!!GOOD!!!
        return std::string_view(m_str).substr(1u);
    }

    // ...
};

void TestStringOwner(const char * pStr) {
  StringOwner so(pStr);
  LOG_DBG("pStr: %s", pStr);
}

void TestStringView(std::string_view str) {
  StringOwner so(str.data());
  LOG_DBG("str: %s", str.data());
}

void TestStringStream(std::string_view str) {
  std::stringstream ss;
  ss << str;
  LOG_DBG("str: %s", ss.str().c_str());
}

void Test1() {
    uint16_t m_iPort;
    long cpp_version = __cplusplus;

    std::cout << "C++ Standard Version: " << cpp_version <<  " " << m_iPort<< std::endl;
    TestStringOwner("TestStringOwner");
    LOG_BR();
    TestStringView("TestStringView");
    LOG_BR();
    std::string str("test std::string");
    TestStringView(str);
    LOG_BR();
    TestStringStream("test string stream");
}
