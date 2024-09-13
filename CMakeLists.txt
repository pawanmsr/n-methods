cmake_minimum_required(VERSION 3.22.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(n-methods VERSION 0.0.1 LANGUAGES CXX)

# GTest
# GTest Primer: https://google.github.io/googletest/
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/0953a17a4281fc26831da647ad3fcd5e21e6473b.zip
  # Update the hash from commit history:
  # https://github.com/google/googletest/commits/main/
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Test
enable_testing()
add_subdirectory(src)
add_subdirectory(test)
