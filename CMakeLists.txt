cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
project(comp-club-task LANGUAGES CXX VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(lib)
add_subdirectory(app)