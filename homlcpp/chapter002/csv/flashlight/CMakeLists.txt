cmake_minimum_required(VERSION 3.22)
project(flashlight-csv-sample)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(
       -Wall -Wextra -msse3 -fopenmp
       $<$<CONFIG:RELEASE>:-Ofast>
       $<$<CONFIG:DEBUG>:-O0>
       $<$<CONFIG:DEBUG>:-ggdb3>
)

add_compile_definitions(
        $<$<CONFIG:RELEASE>:NDEBUG>
)

# flashlight is installed manually under development/libs; ArrayFire lives in /opt
list(APPEND CMAKE_PREFIX_PATH
     "${CMAKE_CURRENT_LIST_DIR}/../../../../development/libs"
     "/opt/ArrayFire-3.9.0-Linux")
find_package(flashlight CONFIG REQUIRED)

find_path(FAST_CPP_CSV_PARSER_INCLUDE_DIR csv.h
    PATH_SUFFIXES fast-cpp-csv-parser)
if(NOT FAST_CPP_CSV_PARSER_INCLUDE_DIR)
    message(FATAL_ERROR "Could not find fast-cpp-csv-parser header csv.h")
endif()

add_executable(csv_flashlight csv_flashlight.cpp)
target_include_directories(csv_flashlight PRIVATE ${FAST_CPP_CSV_PARSER_INCLUDE_DIR})
target_link_libraries(csv_flashlight flashlight::flashlight)
