cmake_minimum_required(VERSION 3.30)
project(recursion)

set(CMAKE_CXX_STANDARD 20)

add_executable(recursion src/main.cpp
        include/bottle.cpp
        include/bottle.h)
