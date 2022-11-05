###############################
#                             #
# Copyright (c) 2022 Selenika #
#                             #
###############################

cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(BIN_NAME qqq)

# set the project name
project(${BIN_NAME})

include_directories(${CMAKE_SOURCE_DIR})
include_directories(../../../../base)

find_package(Threads REQUIRED)

add_executable(${BIN_NAME}
        ../../common/move_only_class.cpp
        main.cpp
        test1.cpp
)

target_link_libraries(${BIN_NAME} ${CMAKE_THREAD_LIBS_INIT} -static-libgcc -static-libstdc++)


