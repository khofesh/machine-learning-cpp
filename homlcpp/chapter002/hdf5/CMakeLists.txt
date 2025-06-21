cmake_minimum_required(VERSION 3.10)
project(hdf5_sample)

find_package(HDF5 1.14.6 REQUIRED)
find_package(HighFive 2.10.1 REQUIRED)
find_package(nlohmann_json 3.11.2 REQUIRED)

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

set(SOURCES hdf5.cpp
            ../json/paper.h
            ../json/review.h
            ../json/reviewsreader.h
            ../json/reviewsreader.cpp)

add_executable(hdf5_sample ${SOURCES})
target_link_libraries(hdf5_sample nlohmann_json::nlohmann_json HighFive)
