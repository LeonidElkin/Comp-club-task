cmake_minimum_required(VERSION 3.31 FATAL_ERROR)
project(comp-club-task LANGUAGES CXX VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_CLANG_TIDY clang-tidy)

add_executable(main main.cpp)