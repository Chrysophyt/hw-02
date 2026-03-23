cmake_minimum_required(VERSION 3.10)
project(MatrixProject)

# --- Global Settings ---
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Coverage flags (Standard way to apply to all targets)
add_compile_options(--coverage -O0)
add_link_options(--coverage)

# --- Linter Setup ---
find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
if(CLANG_TIDY_EXE)
    set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE};--warnings-as-errors=*")
endif()

# --- External Dependencies ---
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.tar.gz
)
FetchContent_MakeAvailable(googletest)

# --- Targets ---

# Main library: All matrix logic goes here
add_library(matrix_lib src/matrix.cpp)
target_include_directories(matrix_lib PUBLIC include)

# Main Application
add_executable(matrix_app src/main.cpp)
target_link_libraries(matrix_app PRIVATE matrix_lib)

# Tests
add_executable(matrix_test test/matrix_test.cpp)
target_link_libraries(matrix_test PRIVATE gtest_main matrix_lib)

# --- Test Discovery ---
include(GoogleTest)
gtest_discover_tests(matrix_test)
