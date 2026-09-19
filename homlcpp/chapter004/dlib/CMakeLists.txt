cmake_minimum_required(VERSION 3.22)
project(dlib-cuda-sample)

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

# Use the manually installed dlib built with CUDA + cuDNN + GUI
set(dlib_DIR ${CMAKE_SOURCE_DIR}/development/libs/lib64/cmake/dlib)
find_package(dlib CONFIG REQUIRED)

add_executable(cuda-dlib "cuda_dlib.cc")
target_link_libraries(cuda-dlib dlib::dlib)

# ArrayFire's bundled cuDNN (9.8) is first in LD_LIBRARY_PATH and shadows the
# system cuDNN (9.12) dlib was built against. Emit DT_RPATH instead of DT_RUNPATH
# so the dlib/cuDNN paths take precedence over LD_LIBRARY_PATH.
target_link_options(cuda-dlib PRIVATE "LINKER:--disable-new-dtags")

