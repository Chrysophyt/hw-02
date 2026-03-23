cmake_minimum_required(VERSION 3.10)
project(MatrixProject)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")

find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
if(CLANG_TIDY_EXE)
    set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}")
else()
    message(WARNING "clang-tidy not found! Linting will be skipped.")
endif()

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)

FetchContent_MakeAvailable(googletest)

add_library(matrix_lib src/matrix.cpp)
target_include_directories(matrix_lib PUBLIC include)

add_executable(matrix_app 
    src/main.cpp 
    src/matrix.cpp
)

add_executable(matrix_test 
    test/matrix_test.cpp
)

target_link_libraries(matrix_test gtest_main matrix_lib)
target_link_libraries(matrix_app matrix_lib)

include(GoogleTest)
gtest_discover_tests(matrix_test)
