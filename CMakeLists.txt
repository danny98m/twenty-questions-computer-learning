cmake_minimum_required(VERSION 3.8)
project(a5)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES constants.h Node.cpp Node.h Tree.cpp Tree.h main.cpp)
add_executable(a5 ${SOURCE_FILES})