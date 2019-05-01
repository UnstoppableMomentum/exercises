#ifndef LOGS_H
#define LOGS_H
#include <iostream>
#define LOG_FUNC() std::cout << __PRETTY_FUNCTION__ <<  std::endl;
#define LOG_BEG() std::cout << __PRETTY_FUNCTION__ << ">>>" << std::endl;
#define LOG_END() std::cout << __PRETTY_FUNCTION__ << "<<<" << std::endl;
#define LOG_BR() std::cout << "----------------" << std::endl;
#endif // LOGS_H
