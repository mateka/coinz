find_package(GTest REQUIRED)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

include(GoogleTest)
include(AddCompileFailureTest/AddCompileFailureTest)

add_executable(
    coinz_tests
    tuple/partial_sum_tests.cpp
    tuple/find_type_tests.cpp
    binary_to_nary_tests.cpp
    make_tail_index_sequence_tests.cpp
    currency_tests.cpp
)
target_link_libraries(
    coinz_tests
    PUBLIC
        coinz
        GTest::GTest
        GTest::Main
)

gtest_discover_tests(coinz_tests)

get_target_property(coinz_INCLUDES coinz::coinz INTERFACE_INCLUDE_DIRECTORIES)
add_compile_failure_test(
    NAME FailOnUnknownTypeInTuple
    SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/tuple/failing_find_type_test.cpp
    INCLUDE_DIRECTORIES coinz_INCLUDES>
)
