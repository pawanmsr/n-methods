set(SIMPLE_TEST_EXECUTABLE simple_test)
set(GOOGLE_TEST_EXECUTABLE google_test)

add_executable(${SIMPLE_TEST_EXECUTABLE} simple_test.cpp)
add_executable(${GOOGLE_TEST_EXECUTABLE} google_test.cpp)

target_link_libraries(
    ${SIMPLE_TEST_EXECUTABLE} PRIVATE
    ${PROJECT_NAME}
)

target_link_libraries(
    ${GOOGLE_TEST_EXECUTABLE} PRIVATE
    ${PROJECT_NAME}
    GTest::gtest_main
)

# GTest
include(GoogleTest)
gtest_discover_tests(${GOOGLE_TEST_EXECUTABLE})

# Simple Tests
add_test(
    NAME test_primes 
    COMMAND ${SIMPLE_TEST_EXECUTABLE} "primes" 
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/build
)

add_test(
    NAME test_binary_exponentiation 
    COMMAND ${SIMPLE_TEST_EXECUTABLE} "exponentiation" 
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/build
)

add_test(
    NAME test_gcd 
    COMMAND ${SIMPLE_TEST_EXECUTABLE} "gcd" 
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/build
)

add_test(
    NAME sort 
    COMMAND ${SIMPLE_TEST_EXECUTABLE} "sort" 
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/build
)

add_test(
    NAME modulo 
    COMMAND ${SIMPLE_TEST_EXECUTABLE} "modulo" 
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/build
)
