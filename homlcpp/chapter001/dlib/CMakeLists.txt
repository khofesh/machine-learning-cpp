cmake_minimum_required(VERSION 3.22)
project(dlib-samples)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)  # Match root project
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

add_executable(linalg-dlib "linalg_dlib.cpp")
target_link_libraries(linalg-dlib dlib::dlib)

add_executable(linreg-dlib "linreg_dlib.cpp")
target_link_libraries(linreg-dlib dlib::dlib)
