add_library(
    ${PROJECT_NAME}
    binary_exponentiation.cpp
    extended_gcd.cpp
    gcd.cpp
    primes.cpp
)
# Library is STATIC by default.

target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/include")
