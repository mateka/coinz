find_package(GTest REQUIRED)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

include(GoogleTest)
include(AddCompileFailureTest/AddCompileFailureTest)

add_executable(
    coinz_tests
    get_n_tests.cpp
    binary_to_nary_tests.cpp
    i_tail_tests.cpp
    to_ratio_tests.cpp
	find_type_tests.cpp
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
    NAME FailOnFindingUnknownType
    SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/failing_find_type_test.cpp
    INCLUDE_DIRECTORIES ${coinz_INCLUDES}>
)
