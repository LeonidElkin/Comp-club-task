cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
project(comp-club-task LANGUAGES CXX VERSION 1.0)

option(BUILD_TESTING "enable test" OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_definitions(PROJECT_SOURCE_DIR="${CMAKE_SOURCE_DIR}")
add_subdirectory(lib)
add_subdirectory(app)

if (BUILD_TESTING)
    include(FetchContent)

    FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG v1.17.0
    )

    FetchContent_MakeAvailable(googletest)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    enable_testing()
    add_subdirectory(tests)
endif ()