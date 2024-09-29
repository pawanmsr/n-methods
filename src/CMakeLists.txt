set(SOURCES binary_exponentiation.cpp extended_gcd.cpp
    gcd.cpp primes.cpp sort.cpp search.cpp modulo_operations.cpp
    combinatorics.cpp union_find.cpp)

add_library(
    ${PROJECT_NAME}
    ${SOURCES}
)
# Library is STATIC by default.

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
