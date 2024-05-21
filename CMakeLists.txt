cmake_minimum_required(VERSION 3.22.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(nmethods VERSION 0.0.1 LANGUAGES CXX)

enable_testing()
add_subdirectory(src)
add_subdirectory(tests)
