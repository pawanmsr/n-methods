set(SOURCES exponentiation.cpp gcd.cpp primes.cpp sort.cpp
    search.cpp modulo.cpp combinatorics.cpp graph.cpp trees.cpp
        newton.cpp interpolation.cpp random.cpp table.cpp)

add_library(
    ${PROJECT_NAME}
    ${SOURCES}
)
# Library is STATIC by default.

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
