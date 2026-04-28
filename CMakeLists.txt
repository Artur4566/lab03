cmake_minimum_required(VERSION 3.10)
project(lab03)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Библиотека из lab02
add_library(print STATIC sources/print.cpp)
target_include_directories(print PUBLIC include)

# Оригинальные примеры из lab02
add_executable(example1 examples/example1.cpp)
add_executable(example2 examples/example2.cpp)
target_link_libraries(example1 print)
target_link_libraries(example2 print)

# Домашнее задание
add_subdirectory(formatter_lib)
add_subdirectory(formatter_ex_lib)
add_subdirectory(solver_lib)
add_subdirectory(hello_world_application)
add_subdirectory(solver_application)

# Установка
install(TARGETS print ARCHIVE DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)
