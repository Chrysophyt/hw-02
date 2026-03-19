cmake_minimum_required(VERSION 3.10)
project(MatrixProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(MatrixApp 
    src/main.cpp 
    src/Matrix.cpp
)

target_include_directories(MatrixApp PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
