###############################
#                             #
# Copyright (c) 2022 Selenika #
#                             #
###############################

cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(Boost_USE_STATIC_LIBS ON)



add_definitions(-DDEBUG)

# set the project name
project(qqq)

include_directories(${CMAKE_SOURCE_DIR})
include_directories(options)

find_package(Boost 1.77.0 COMPONENTS log regex program_options thread system REQUIRED)

# add the executable
add_executable(qqq
        main.cpp
        test1.cpp
        )

target_link_libraries(qqq ${Boost_LIBRARIES})
