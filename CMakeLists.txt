cmake_minimum_required(VERSION 3.10)
project(MachineLearningCpp VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(LIBS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/development/libs)
set(CMAKE_PREFIX_PATH ${LIBS_DIR}/libtorch ${CMAKE_PREFIX_PATH})

# add "include" directories for all dependencies
include_directories(${LIBS_DIR}/include)

# Enable testing
enable_testing()

# Add subdirectories for each category
add_subdirectory(homlcpp)
add_subdirectory(check_torch)
