###############################
#                             #
# Copyright (c) 2022 Selenika #
#                             #
###############################

cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(Boost_USE_STATIC_LIBS ON)
set(BIN_NAME qqq)

# set the project name
project(${BIN_NAME})

include_directories(${CMAKE_SOURCE_DIR})

find_package(Boost 1.77.0 COMPONENTS log regex thread system REQUIRED)

# add the executable
add_executable(${BIN_NAME}
        test1.cpp
        test2.cpp
)


