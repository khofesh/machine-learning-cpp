cmake_minimum_required(VERSION 3.22)
project(xtensor)

# find_package(xtensor 0.25.0 REQUIRED)
# find_package(xtensor-blas 0.21.0 REQUIRED)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_VERBOSE_MAKEFILE ON)

add_compile_options(
       -Wall -Wextra -msse3
       $<$<CONFIG:RELEASE>:-Ofast>
       $<$<CONFIG:DEBUG>:-O0>
       $<$<CONFIG:DEBUG>:-ggdb3>
)

add_compile_definitions(
        $<$<CONFIG:RELEASE>:NDEBUG>
)

add_executable(linalg_xtensor "linalg_xtensor.cc")
target_include_directories(linalg_xtensor PRIVATE ${CMAKE_SOURCE_DIR}/development/libs/include)
target_link_libraries(linalg_xtensor blas)
