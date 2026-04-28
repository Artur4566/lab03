cmake_minimum_required(VERSION 3.4)
project(lab03)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Библиотека
add_subdirectory(library)

# Примеры
add_subdirectory(examples)

# Тесты (опционально)
# add_subdirectory(tests)
