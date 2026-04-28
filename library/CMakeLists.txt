cmake_minimum_required(VERSION 3.4)
project(library)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(library STATIC output.cpp)
target_include_directories(library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
