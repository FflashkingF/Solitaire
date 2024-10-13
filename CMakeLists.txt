cmake_minimum_required(VERSION 3.20)

project(Solitaire)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

set(GCC_COVERAGE_COMPILE_FLAGS "-O0")
set(CMAKE_CXX_FLAGS ${GCC_COVERAGE_COMPILE_FLAGS})

add_executable(Solitaire solitaire.cpp)
