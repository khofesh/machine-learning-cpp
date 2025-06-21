cmake_minimum_required(VERSION 3.10)
project(flashlight-csv-sample)

# Set C++ standard
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_VERBOSE_MAKEFILE ON)

# Add compile options
add_compile_options(
       -Wall -Wextra -msse3 -fopenmp
       $<$<CONFIG:RELEASE>:-Ofast>
       $<$<CONFIG:DEBUG>:-O0>
       $<$<CONFIG:DEBUG>:-ggdb3>
)

add_compile_definitions(
        $<$<CONFIG:RELEASE>:NDEBUG>
)

# Use your custom development directories
set(CUSTOM_LIBS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../../development/libs)
set(ARRAYFIRE_DIR /opt/ArrayFire-3.9.0-Linux)

# Add ArrayFire to CMAKE_PREFIX_PATH for find_package
list(APPEND CMAKE_PREFIX_PATH ${ARRAYFIRE_DIR})

# Try to find ArrayFire using find_package first
find_package(ArrayFire QUIET)

# Try to find Flashlight in your custom libs first
find_library(FLASHLIGHT_LIB
    NAMES flashlight
    PATHS ${CUSTOM_LIBS_DIR}/lib ${CUSTOM_LIBS_DIR}/lib64
    NO_DEFAULT_PATH
)

if(NOT FLASHLIGHT_LIB)
    message(FATAL_ERROR "Could not find Flashlight library in ${CUSTOM_LIBS_DIR}/lib or ${CUSTOM_LIBS_DIR}/lib64")
endif()

message(STATUS "Found custom Flashlight library: ${FLASHLIGHT_LIB}")
message(STATUS "Using custom libs directory: ${CUSTOM_LIBS_DIR}")
message(STATUS "Using ArrayFire directory: ${ARRAYFIRE_DIR}")

# Set up ArrayFire libraries (same as ArrayFire CMakeLists.txt)
if(ArrayFire_FOUND)
    message(STATUS "ArrayFire found via find_package")
    message(STATUS "ArrayFire version: ${ArrayFire_VERSION}")
else()
    message(STATUS "ArrayFire not found via find_package, setting up manually...")
    
    # Manual ArrayFire setup
    set(ArrayFire_INCLUDE_DIRS ${ARRAYFIRE_DIR}/include)
    set(ArrayFire_LIBRARY_DIRS ${ARRAYFIRE_DIR}/lib64)
    
    # Find ArrayFire libraries
    find_library(AF_LIB 
        NAMES af
        PATHS ${ArrayFire_LIBRARY_DIRS}
        NO_DEFAULT_PATH
    )
    
    find_library(AF_CPU_LIB 
        NAMES afcpu
        PATHS ${ArrayFire_LIBRARY_DIRS}
        NO_DEFAULT_PATH
    )
    
    # Check if libraries were found
    if(NOT AF_LIB)
        message(FATAL_ERROR "ArrayFire main library not found in ${ArrayFire_LIBRARY_DIRS}")
    endif()
    
    if(NOT AF_CPU_LIB)
        message(FATAL_ERROR "ArrayFire CPU library not found in ${ArrayFire_LIBRARY_DIRS}")
    endif()
    
    message(STATUS "Found ArrayFire main library: ${AF_LIB}")
    message(STATUS "Found ArrayFire CPU library: ${AF_CPU_LIB}")
    
    # Set ArrayFire_LIBRARIES
    set(ArrayFire_LIBRARIES ${AF_LIB} ${AF_CPU_LIB})
    
    # Check if include directory exists
    if(EXISTS ${ArrayFire_INCLUDE_DIRS})
        message(STATUS "Found ArrayFire include directory: ${ArrayFire_INCLUDE_DIRS}")
    else()
        message(WARNING "ArrayFire include directory not found: ${ArrayFire_INCLUDE_DIRS}")
    endif()
endif()

# Add the executable
add_executable(csv_flashlight csv_flashlight.cpp)

# Set C++ standard for target
target_compile_features(csv_flashlight PRIVATE cxx_std_20)

# Add include directories
target_include_directories(csv_flashlight SYSTEM PRIVATE 
    ${CUSTOM_LIBS_DIR}/include
    ${ArrayFire_INCLUDE_DIRS}
)

# Link libraries
if(ArrayFire_FOUND AND TARGET ArrayFire::afcpu)
    # Use modern CMake targets if available
    target_link_libraries(csv_flashlight ${FLASHLIGHT_LIB} ArrayFire::afcpu)
    message(STATUS "Linking csv_flashlight with modern ArrayFire target")
else()
    # Use traditional linking with full library paths
    target_link_libraries(csv_flashlight ${FLASHLIGHT_LIB} ${AF_LIB} ${AF_CPU_LIB})
    message(STATUS "Linking csv_flashlight with libraries: ${FLASHLIGHT_LIB} ${AF_LIB} ${AF_CPU_LIB}")
    
    # Add RPATH so the executable can find the libraries at runtime
    set_target_properties(csv_flashlight PROPERTIES
        INSTALL_RPATH "${ARRAYFIRE_DIR}/lib64:${CUSTOM_LIBS_DIR}/lib64:${CUSTOM_LIBS_DIR}/lib"
        BUILD_WITH_INSTALL_RPATH TRUE
        INSTALL_RPATH_USE_LINK_PATH TRUE
    )
endif()

# Link with system libraries that ArrayFire and Flashlight depend on
target_link_libraries(csv_flashlight pthread dl m rt)

# Handle fast-cpp-csv-parser
if(DEFINED ENV{VCPKG_ROOT})
    set(FAST_CPP_CSV_PARSER_INCLUDE_DIRS "$ENV{VCPKG_ROOT}/installed/${VCPKG_TARGET_TRIPLET}/include/fast-cpp-csv-parser")
    target_include_directories(csv_flashlight PRIVATE ${FAST_CPP_CSV_PARSER_INCLUDE_DIRS})
    message(STATUS "Using VCPKG_ROOT: $ENV{VCPKG_ROOT}")
    message(STATUS "Fast CSV Parser include dir: ${FAST_CPP_CSV_PARSER_INCLUDE_DIRS}")
else()
    message(WARNING "VCPKG_ROOT environment variable not set")
    find_path(FAST_CPP_CSV_PARSER_INCLUDE_DIRS "csv.h"
        PATHS ${CUSTOM_LIBS_DIR}/include
        NO_DEFAULT_PATH
    )
    if(FAST_CPP_CSV_PARSER_INCLUDE_DIRS)
        target_include_directories(csv_flashlight PRIVATE ${FAST_CPP_CSV_PARSER_INCLUDE_DIRS})
        message(STATUS "Found fast-cpp-csv-parser at: ${FAST_CPP_CSV_PARSER_INCLUDE_DIRS}")
    else()
        message(FATAL_ERROR "Could not find fast-cpp-csv-parser headers")
    endif()
endif()

# Add OpenMP if needed by Flashlight
find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(csv_flashlight OpenMP::OpenMP_CXX)
    message(STATUS "Linking with OpenMP")
endif()

# Print summary
message(STATUS "=== Flashlight Configuration Summary ===")
message(STATUS "Flashlight library: ${FLASHLIGHT_LIB}")
message(STATUS "ArrayFire libraries: ${ArrayFire_LIBRARIES}")
message(STATUS "Custom libs directory: ${CUSTOM_LIBS_DIR}")
message(STATUS "ArrayFire directory: ${ARRAYFIRE_DIR}")
message(STATUS "========================================")
