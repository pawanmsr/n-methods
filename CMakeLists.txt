cmake_minimum_required(VERSION 3.22.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(n-methods VERSION 1.0)

add_subdirectory(src)

enable_testing()
add_subdirectory(tests)
