set(TEST_EXECUTABLE simple_test)

add_executable(${TEST_EXECUTABLE} simple_test.cpp)

target_link_libraries(
    ${TEST_EXECUTABLE} PRIVATE
    ${PROJECT_NAME}
    GTest::gtest_main
)

# include(GoogleTest)
# gtest_discover_tests(${TEST_EXECUTABLE})

add_test(
    NAME test_primes 
    COMMAND ${TEST_EXECUTABLE} "primes" 
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/build
)

add_test(
    NAME test_binary_exponentiation 
    COMMAND ${TEST_EXECUTABLE} "binary_exponentiation" 
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/build
)

add_test(
    NAME test_gcd 
    COMMAND ${TEST_EXECUTABLE} "gcd" 
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/build
)

add_test(
    NAME extended_gcd 
    COMMAND ${TEST_EXECUTABLE} "extended_gcd" 
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/build
)
