cmake_minimum_required(VERSION 3.18 FATAL_ERROR)
project(torch_test)

# Set path to your extracted LibTorch directory
# set(CMAKE_PREFIX_PATH /media/wdhome/github/khofesh/machine-learning-cpp/development/libs/libtorch)

find_package(Torch REQUIRED)

add_executable(example example.cpp)
target_link_libraries(example "${TORCH_LIBRARIES}")
set_property(TARGET example PROPERTY CXX_STANDARD 17)
