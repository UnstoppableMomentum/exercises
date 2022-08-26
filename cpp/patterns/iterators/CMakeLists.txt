cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC_LIST
        ${CMAKE_SOURCE_DIR}/main.cpp
        ${CMAKE_SOURCE_DIR}/test1.cpp
        ${CMAKE_SOURCE_DIR}/message.cpp
        ${CMAKE_SOURCE_DIR}/message_parser.cpp
        ${CMAKE_SOURCE_DIR}/message_parser_sign_in.cpp
)

# set the project name
project(qqq)

# add the executable
add_executable(qqq ${SRC_LIST})
