cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC_LIST
        # audio
        ${CMAKE_SOURCE_DIR}/main.cpp
        ${CMAKE_SOURCE_DIR}/test1.cpp
        ${CMAKE_SOURCE_DIR}/test2.cpp
        ${CMAKE_SOURCE_DIR}/test3.cpp
        ${CMAKE_SOURCE_DIR}/test4.cpp
        ${CMAKE_SOURCE_DIR}/test5.cpp
        ${CMAKE_SOURCE_DIR}/test6.cpp
        ${CMAKE_SOURCE_DIR}/test7.cpp
        ${CMAKE_SOURCE_DIR}/test8.cpp
        ${CMAKE_SOURCE_DIR}/test9.cpp
        ${CMAKE_SOURCE_DIR}/test10.cpp
)

# set the project name
project(qqq)

# add the executable
add_executable(qqq ${SRC_LIST})
