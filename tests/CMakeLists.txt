add_executable(
    tests
    simple_test.cpp
)

target_link_libraries(tests PRIVATE ${PROJECT_NAME})
target_include_directories(tests PUBLIC "${PROJECT_SOURCE_DIR}/include")
