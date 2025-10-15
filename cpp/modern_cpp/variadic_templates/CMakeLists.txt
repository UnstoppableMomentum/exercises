###############################
#                             #
# Copyright (c) 2025 Selenika #
#                             #
###############################

cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set the project name
project(variadic-templates)

include_directories(${CMAKE_SOURCE_DIR})

# set source list
set(SRC_LIST
       ${CMAKE_SOURCE_DIR}/main.cpp
       ${CMAKE_SOURCE_DIR}/test1.cpp
       ${CMAKE_SOURCE_DIR}/test2.cpp
)

# add the executable
add_executable(qqq ${SRC_LIST})
