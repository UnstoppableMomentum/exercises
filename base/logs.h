#ifndef LOGS_H
#define LOGS_H

#include <iostream>

#define LOG_FUNC()      std::cout << __PRETTY_FUNCTION__ <<  std::endl;
#define LOG_FUNC_LINE() std::cout << __PRETTY_FUNCTION__ << " " << __LINE__ <<  std::endl;
#define LOG_BEG()       std::cout << __PRETTY_FUNCTION__ << ">>>" << std::endl;
#define LOG_END()       std::cout << __PRETTY_FUNCTION__ << "<<<" << std::endl;
#define LOG_BR()        std::cout << "----------------"  << std::endl;

#define LOG_DBG(Format, ...)    printf ("%s"       Format "\n", __PRETTY_FUNCTION__, __VA_ARGS__)
#define LOG_DBG_0(Format, ...)  printf (Format "\n", __VA_ARGS__)
#define LOG_DBG_LN(Format, ...) printf ("[%s:%u] " Format "\n", __PRETTY_FUNCTION__, __LINE__, __VA_ARGS__)

#endif // LOGS_H
