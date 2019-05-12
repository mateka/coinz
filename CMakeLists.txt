cmake_minimum_required (VERSION 3.10)

project(
    "coinz"
    VERSION 0.0.0.1
    DESCRIPTION "Library for fantasy money and currencies."
    HOMEPAGE_URL "https://github.com/mateka/coinz"
    LANGUAGES CXX
)

# Project dependencies

# Project definition
add_library(coinz INTERFACE)
target_sources(
    coinz
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/coinz/tuple_partial_sum.hpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/coinz/currency.hpp>
        $<INSTALL_INTERFACE:include/coinz/tuple_partial_sum.hpp>
        $<INSTALL_INTERFACE:include/coinz/currency.hpp>
)
target_compile_features(
    coinz
    INTERFACE cxx_std_20
)
target_include_directories(
    coinz
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# Install part
include(CMakePackageConfigHelpers)

add_library(coinz::coinz ALIAS coinz)

configure_package_config_file(
    "coinzConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/coinzConfig.cmake"
    INSTALL_DESTINATION lib/cmake/coinz
)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/coinzConfigVersion.cmake"
    VERSION ${coinz_VERSION}
    COMPATIBILITY SameMajorVersion
)
install(
    TARGETS coinz EXPORT coinzTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)
install(
    EXPORT coinzTargets
    FILE coinzTargets.cmake
    NAMESPACE coinz::
    DESTINATION lib/cmake/coinz
)
install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/coinzConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/coinzConfigVersion.cmake"
    DESTINATION lib/cmake/coinz
)

# Tests part
enable_testing()
add_subdirectory(tests)

# Examples part
#add_subdirectory(examples)
