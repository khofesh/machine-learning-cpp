cmake_minimum_required(VERSION 3.22)
project(dlib-samples)

set(LIBS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../development/libs)

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

# include dlib headers
include_directories(${LIBS_DIR}/include)

# find the static dlib library
find_library(DLIB_LIBRARY
    NAMES dlib
    PATHS ${LIBS_DIR}/lib64
    NO_DEFAULT_PATH
)

if(NOT DLIB_LIBRARY)
    message(FATAL_ERROR "Could not find dlib library in ${LIBS_DIR}/lib64")
endif()

add_executable(linalg-dlib "linalg_dlib.cpp")
# target_link_libraries(linalg-dlib dlib::dlib)
target_link_libraries(linalg-dlib ${DLIB_LIBRARY})

# Link required system libraries for dlib
target_link_libraries(linalg-dlib pthread)

# add_executable(linreg-dlib "linreg_dlib.cc")
# target_link_libraries(linreg-dlib dlib::dlib)

