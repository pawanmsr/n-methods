set(TEST_EXECUTABLE simple_test)

add_executable(${TEST_EXECUTABLE} simple_test.cpp)
target_link_libraries(${TEST_EXECUTABLE} PRIVATE ${PROJECT_NAME})

add_test(NAME test_primes COMMAND ${TEST_EXECUTABLE} "primes")
add_test(NAME test_binary_exponentiation COMMAND ${TEST_EXECUTABLE} "binary_exponentiation")
add_test(NAME test_gcd COMMAND ${TEST_EXECUTABLE} "gcd")
add_test(NAME extended_gcd COMMAND ${TEST_EXECUTABLE} "extended_gcd")
