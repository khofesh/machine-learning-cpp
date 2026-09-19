cmake_minimum_required(VERSION 3.22)
project(dlib-sample)

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

# Find dlib via vcpkg
find_package(dlib CONFIG REQUIRED)

set(PLOTCPP_PATH "${CMAKE_CURRENT_LIST_DIR}/../../../development/libs/sources/plotcpp"
    CACHE PATH "path to plotcpp sources dir")

add_executable(grid-dlib "grid-dlib.cc")
target_include_directories(grid-dlib PRIVATE ${PLOTCPP_PATH})
target_link_libraries(grid-dlib dlib::dlib)
