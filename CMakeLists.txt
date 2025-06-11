cmake_minimum_required(VERSION 3.10)
project(MachineLearningCpp VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# vcpkg integration
# if(DEFINED ENV{VCPKG_ROOT})
#     set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
# endif()
set (VCPKG_DIR /home/fahmad/vcpkg)
include(${VCPKG_DIR}/scripts/buildsystems/vcpkg.cmake)

set(LIBS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/development/libs)
set(CMAKE_PREFIX_PATH ${LIBS_DIR}/libtorch ${CMAKE_PREFIX_PATH})

# add "include" directories for all dependencies (keep for other libs)
# causes dlib vcpkg
# make it available to subdirectories that need it
set(MANUAL_LIBS_INCLUDE_DIR ${LIBS_DIR}/include)
# to use it, add in the specific cmakelist
# target_include_directories(your_target PRIVATE ${MANUAL_LIBS_INCLUDE_DIR})

# Enable testing
enable_testing()

# Add subdirectories for each category  
add_subdirectory(homlcpp)
add_subdirectory(check_torch)
