find_package(GTest REQUIRED)

include(GoogleTest)

add_executable(
    coins_tests
    currency_tests.cpp
)
target_link_libraries(
    coins_tests
    PUBLIC
        coinz
        GTest::GTest
        GTest::Main
)

gtest_discover_tests(coins_tests)
