cmake_minimum_required(VERSION 2.8.4)
project(tp2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    date.cpp
    date.h
    pile.h
    succ.cpp
    succ.h
    tp2.cpp)

add_executable(tp2 ${SOURCE_FILES})