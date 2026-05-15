cmake_minimum_required(VERSION 3.10)
project(solver_application)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(solver_application solver.cpp)
target_link_libraries(solver_application PRIVATE formatter_ex_lib solver_lib)
