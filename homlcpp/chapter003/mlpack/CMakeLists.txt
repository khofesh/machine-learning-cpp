cmake_minimum_required(VERSION 3.22)
project(mlpack-sample)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/cmake")
find_package(mlpack REQUIRED)
find_package(Armadillo CONFIG REQUIRED)

add_compile_options(
       -Wall -Wextra -msse3 -fopenmp
       $<$<CONFIG:RELEASE>:-Ofast>
       $<$<CONFIG:DEBUG>:-O0>
       $<$<CONFIG:DEBUG>:-ggdb3>
)

add_link_options(-fopenmp)

add_compile_definitions(
        $<$<CONFIG:RELEASE>:NDEBUG>
)

set(PLOTCPP_PATH "${CMAKE_CURRENT_LIST_DIR}/../../../development/libs/sources/plotcpp"
    CACHE PATH "path to plotcpp sources dir")

add_executable(grid-mlpack "grid-mlpack.cc")
target_include_directories(grid-mlpack PRIVATE ${PLOTCPP_PATH} ${MLPACK_INCLUDE_DIR})
target_link_libraries(grid-mlpack armadillo)
