cmake_minimum_required(VERSION 3.22)
project(blaze)

set(LIBS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../development/libs)
set(CMAKE_PREFIX_PATH ${LIBS_DIR}/share/blaze ${CMAKE_PREFIX_PATH})

find_package(blaze 3.8.2 REQUIRED)

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

add_executable(linalg_blaze "linalg_blaze.cpp")
target_link_libraries(linalg_blaze blas lapack blaze::blaze)

add_executable(linreg_blaze "linreg_blaze.cpp")
target_link_libraries(linreg_blaze blas lapack blaze::blaze)

