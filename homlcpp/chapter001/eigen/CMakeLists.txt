cmake_minimum_required(VERSION 3.22 FATAL_ERROR)
project(eigen)

find_package(OpenMP)
find_package(Eigen3 3.4.0 REQUIRED)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_VERBOSE_MAKEFILE ON)

# set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} /media/wdhome/github/khofesh/machine-learning-cpp/development/libs/)

add_compile_options(
       -Wall -Wextra -msse3
       $<$<CONFIG:RELEASE>:-Ofast>
       $<$<CONFIG:DEBUG>:-O0>
       $<$<CONFIG:DEBUG>:-ggdb3>
)

add_compile_definitions(
        $<$<CONFIG:RELEASE>:NDEBUG>
)

add_executable(linalg_eigen "linalg_eigen.cpp")
target_link_libraries(linalg_eigen Eigen3::Eigen OpenMP::OpenMP_CXX)

add_executable(linreg_eigen "linreg_eigen.cpp")
target_link_libraries(linreg_eigen Eigen3::Eigen OpenMP::OpenMP_CXX)
