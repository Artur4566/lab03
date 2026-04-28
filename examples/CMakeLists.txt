cmake_minimum_required(VERSION 3.4)
project(examples)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(demo1 demo1.cpp)
add_executable(demo2 demo2.cpp)

target_link_libraries(demo1 library)
target_link_libraries(demo2 library)
