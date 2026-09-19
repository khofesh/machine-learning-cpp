cmake_minimum_required(VERSION 3.22)
project(grid-flashlight)

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
     "${CMAKE_CURRENT_LIST_DIR}/../../../development/libs"
     "/opt/ArrayFire-3.10.0-Linux")
find_package(flashlight CONFIG REQUIRED)

set(PLOTCPP_PATH "${CMAKE_CURRENT_LIST_DIR}/../../../development/libs/sources/plotcpp"
    CACHE PATH "path to plotcpp sources dir")

add_executable(grid_fl grid_fl.cc)
target_include_directories(grid_fl PRIVATE ${PLOTCPP_PATH})
target_link_libraries(grid_fl flashlight::flashlight)
