cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set the project name
project(qqq)

include_directories(../../../../base)

# add the executable
add_executable(qqq main.cpp test1.cpp)
