cmake_minimum_required(VERSION 3.10)
project(flashlight-csv-sample)

# Set C++ standard
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_VERBOSE_MAKEFILE ON)

# Add compile options
add_compile_options(
       -Wall -Wextra -msse3 -fopenmp
       $<$<CONFIG:RELEASE>:-Ofast>
       $<$<CONFIG:DEBUG>:-O0>
       $<$<CONFIG:DEBUG>:-ggdb3>
)

add_compile_definitions(
        $<$<CONFIG:RELEASE>:NDEBUG>
)

set(CUSTOM_LIBS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../../development/libs)

# find Flashlight in development libs
find_library(FLASHLIGHT_LIB
    NAMES flashlight
    PATHS ${CUSTOM_LIBS_DIR}/lib ${CUSTOM_LIBS_DIR}/lib64
    NO_DEFAULT_PATH
)

if(FLASHLIGHT_LIB)
    message(STATUS "Found custom Flashlight library: ${FLASHLIGHT_LIB}")
    message(STATUS "Using custom libs directory: ${CUSTOM_LIBS_DIR}")
    
    # add the executable
    add_executable(csv_flashlight csv_flashlight.cpp)
    
    # link with custom Flashlight
    target_link_libraries(csv_flashlight ${FLASHLIGHT_LIB})
    
    # add include directories for Flashlight
    target_include_directories(csv_flashlight PRIVATE 
        ${CUSTOM_LIBS_DIR}/include
    )
    
    find_package(Threads REQUIRED)
    target_link_libraries(csv_flashlight Threads::Threads)
    
else()
    message(FATAL_ERROR "Could not find Flashlight library in ${CUSTOM_LIBS_DIR}/lib or ${CUSTOM_LIBS_DIR}/lib64")
endif()

# handle fast-cpp-csv-parser
if(DEFINED ENV{VCPKG_ROOT})
    set(FAST_CPP_CSV_PARSER_INCLUDE_DIRS "$ENV{VCPKG_ROOT}/installed/${VCPKG_TARGET_TRIPLET}/include/fast-cpp-csv-parser")
    target_include_directories(csv_flashlight PRIVATE ${FAST_CPP_CSV_PARSER_INCLUDE_DIRS})
    message(STATUS "Using VCPKG_ROOT: $ENV{VCPKG_ROOT}")
    message(STATUS "Fast CSV Parser include dir: ${FAST_CPP_CSV_PARSER_INCLUDE_DIRS}")
else()
    message(WARNING "VCPKG_ROOT environment variable not set")
    find_path(FAST_CPP_CSV_PARSER_INCLUDE_DIRS "csv.h"
        PATHS ${CUSTOM_LIBS_DIR}/include
        NO_DEFAULT_PATH
    )
    if(FAST_CPP_CSV_PARSER_INCLUDE_DIRS)
        target_include_directories(csv_flashlight PRIVATE ${FAST_CPP_CSV_PARSER_INCLUDE_DIRS})
        message(STATUS "Found fast-cpp-csv-parser at: ${FAST_CPP_CSV_PARSER_INCLUDE_DIRS}")
    else()
        message(FATAL_ERROR "Could not find fast-cpp-csv-parser headers")
    endif()
endif()
