cmake_minimum_required(VERSION 3.22)
project(csv_sample)

find_package(Eigen3 3.4.0 REQUIRED)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_VERBOSE_MAKEFILE ON)

add_compile_options(
       -Wall -Wextra -msse3 -fopenmp
       $<$<CONFIG:RELEASE>:-Ofast>
       $<$<CONFIG:DEBUG>:-O0>
       $<$<CONFIG:DEBUG>:-ggdb3>
)

add_compile_definitions(
        $<$<CONFIG:RELEASE>:NDEBUG>
)

add_executable(csv_sample "csv.cpp")

# Link Eigen3
target_link_libraries(csv_sample Eigen3::Eigen)

# Add fast-cpp-csv-parser include directories
if(DEFINED ENV{VCPKG_ROOT})
    set(FAST_CPP_CSV_PARSER_INCLUDE_DIRS "$ENV{VCPKG_ROOT}/installed/${VCPKG_TARGET_TRIPLET}/include/fast-cpp-csv-parser")
    target_include_directories(csv_sample PRIVATE ${FAST_CPP_CSV_PARSER_INCLUDE_DIRS})
    message(STATUS "Using VCPKG_ROOT: $ENV{VCPKG_ROOT}")
    message(STATUS "Fast CSV Parser include dir: ${FAST_CPP_CSV_PARSER_INCLUDE_DIRS}")
else()
    message(WARNING "VCPKG_ROOT environment variable not set")
    find_path(FAST_CPP_CSV_PARSER_INCLUDE_DIRS "csv.h")
    if(FAST_CPP_CSV_PARSER_INCLUDE_DIRS)
        target_include_directories(csv_sample PRIVATE ${FAST_CPP_CSV_PARSER_INCLUDE_DIRS})
        message(STATUS "Found fast-cpp-csv-parser at: ${FAST_CPP_CSV_PARSER_INCLUDE_DIRS}")
    else()
        message(FATAL_ERROR "Could not find fast-cpp-csv-parser headers")
    endif()
endif()
