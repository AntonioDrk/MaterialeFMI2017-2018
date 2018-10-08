cmake_minimum_required(VERSION 3.8)
project(CLionTest)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES Test.c)
add_executable(CLionTest ${SOURCE_FILES})