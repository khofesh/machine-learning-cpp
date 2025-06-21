cmake_minimum_required(VERSION 3.10)

# Set ArrayFire paths - using system installation in /opt
set(ARRAYFIRE_ROOT /opt/ArrayFire-3.9.0-Linux)

# Add ArrayFire to CMAKE_PREFIX_PATH for find_package
list(APPEND CMAKE_PREFIX_PATH ${ARRAYFIRE_ROOT})

# Try to find ArrayFire using find_package first
find_package(ArrayFire QUIET)

if(ArrayFire_FOUND)
    message(STATUS "ArrayFire found via find_package")
    message(STATUS "ArrayFire version: ${ArrayFire_VERSION}")
else()
    message(STATUS "ArrayFire not found via find_package, setting up manually...")
    
    # Manual ArrayFire setup - using system installation in /opt
    set(ArrayFire_INCLUDE_DIRS ${ARRAYFIRE_ROOT}/include)
    set(ArrayFire_LIBRARY_DIRS ${ARRAYFIRE_ROOT}/lib64)
    
    # Find ALL ArrayFire libraries that might be needed
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
    
    # Find Intel MKL libraries that ArrayFire depends on
    find_library(MKL_RT_LIB 
        NAMES mkl_rt
        PATHS ${ArrayFire_LIBRARY_DIRS}
        NO_DEFAULT_PATH
    )
    
    find_library(MKL_CORE_LIB 
        NAMES mkl_core
        PATHS ${ArrayFire_LIBRARY_DIRS}
        NO_DEFAULT_PATH
    )
    
    find_library(MKL_INTEL_LP64_LIB 
        NAMES mkl_intel_lp64
        PATHS ${ArrayFire_LIBRARY_DIRS}
        NO_DEFAULT_PATH
    )
    
    find_library(MKL_TBB_THREAD_LIB 
        NAMES mkl_tbb_thread
        PATHS ${ArrayFire_LIBRARY_DIRS}
        NO_DEFAULT_PATH
    )
    
    find_library(TBB_LIB 
        NAMES tbb
        PATHS ${ArrayFire_LIBRARY_DIRS}
        NO_DEFAULT_PATH
    )
    
    # Check if main library was found
    if(NOT AF_LIB)
        message(FATAL_ERROR "ArrayFire main library not found in ${ArrayFire_LIBRARY_DIRS}")
    endif()
    
    if(NOT AF_CPU_LIB)
        message(FATAL_ERROR "ArrayFire CPU library not found in ${ArrayFire_LIBRARY_DIRS}")
    endif()
    
    message(STATUS "Found ArrayFire main library: ${AF_LIB}")
    message(STATUS "Found ArrayFire CPU library: ${AF_CPU_LIB}")
    
    # Set ArrayFire_LIBRARIES in the correct order
    # af and afcpu are the core libraries
    set(ArrayFire_LIBRARIES ${AF_LIB} ${AF_CPU_LIB})
    
    # Add MKL libraries if found
    if(MKL_RT_LIB)
        message(STATUS "Found MKL RT library: ${MKL_RT_LIB}")
        list(APPEND ArrayFire_LIBRARIES ${MKL_RT_LIB})
    endif()
    
    if(TBB_LIB)
        message(STATUS "Found TBB library: ${TBB_LIB}")
        list(APPEND ArrayFire_LIBRARIES ${TBB_LIB})
    endif()
    
    # Check if include directory exists
    if(EXISTS ${ArrayFire_INCLUDE_DIRS})
        message(STATUS "Found ArrayFire include directory: ${ArrayFire_INCLUDE_DIRS}")
    else()
        message(WARNING "ArrayFire include directory not found: ${ArrayFire_INCLUDE_DIRS}")
    endif()
endif()

# Create linalg_af executable
add_executable(linalg_af linalg_af.cpp)

# Set C++ standard
target_compile_features(linalg_af PRIVATE cxx_std_17)

# Add include directories
target_include_directories(linalg_af PRIVATE ${ArrayFire_INCLUDE_DIRS})

# Link libraries - be more explicit about linking
if(ArrayFire_FOUND AND TARGET ArrayFire::afcpu)
    # Use modern CMake targets if available
    target_link_libraries(linalg_af ArrayFire::afcpu)
    message(STATUS "Linking linalg_af with modern target: ArrayFire::afcpu")
else()
    # Use the actual library paths we found
    target_link_libraries(linalg_af ${AF_LIB} ${AF_CPU_LIB})
    message(STATUS "Linking linalg_af with libraries: ${AF_LIB} ${AF_CPU_LIB}")
    
    # Add RPATH so the executable can find the libraries at runtime
    set_target_properties(linalg_af PROPERTIES
        INSTALL_RPATH "/opt/ArrayFire-3.9.0-Linux/lib64"
        BUILD_WITH_INSTALL_RPATH TRUE
        INSTALL_RPATH_USE_LINK_PATH TRUE
    )
endif()

# Also need to link with system libraries that ArrayFire depends on
target_link_libraries(linalg_af pthread dl m rt)

# Create linreg_af executable
add_executable(linreg_af linreg_af.cpp)

# Set C++ standard
target_compile_features(linreg_af PRIVATE cxx_std_17)

# Add include directories
target_include_directories(linreg_af PRIVATE ${ArrayFire_INCLUDE_DIRS})

# Link libraries - be more explicit about linking
if(ArrayFire_FOUND AND TARGET ArrayFire::afcpu)
    # Use modern CMake targets if available
    target_link_libraries(linreg_af ArrayFire::afcpu)
    message(STATUS "Linking linreg_af with modern target: ArrayFire::afcpu")
else()
    # Use the actual library paths we found
    target_link_libraries(linreg_af ${AF_LIB} ${AF_CPU_LIB})
    message(STATUS "Linking linreg_af with libraries: ${AF_LIB} ${AF_CPU_LIB}")
    
    # Add RPATH so the executable can find the libraries at runtime
    set_target_properties(linreg_af PROPERTIES
        INSTALL_RPATH "/opt/ArrayFire-3.9.0-Linux/lib64"
        BUILD_WITH_INSTALL_RPATH TRUE
        INSTALL_RPATH_USE_LINK_PATH TRUE
    )
endif()

# Also need to link with system libraries that ArrayFire depends on
target_link_libraries(linreg_af pthread dl m rt)

# Add some common compiler flags for ArrayFire
target_compile_definitions(linalg_af PRIVATE AF_CPU)
target_compile_definitions(linreg_af PRIVATE AF_CPU)

# Add tests if this is part of a testing framework
if(BUILD_TESTING)
    add_test(NAME linalg_af_test COMMAND linalg_af)
    add_test(NAME linreg_af_test COMMAND linreg_af)
endif()

# Print summary
message(STATUS "=== ArrayFire Configuration Summary ===")
if(ArrayFire_FOUND)
    message(STATUS "ArrayFire found via find_package: YES")
    if(TARGET ArrayFire::afcpu)
        message(STATUS "Using modern CMake targets: YES")
    else()
        message(STATUS "Using modern CMake targets: NO (fallback to traditional)")
    endif()
else()
    message(STATUS "ArrayFire found via find_package: NO")
    message(STATUS "Using manual configuration: YES")
endif()
message(STATUS "ArrayFire include dirs: ${ArrayFire_INCLUDE_DIRS}")
message(STATUS "ArrayFire libraries: ${ArrayFire_LIBRARIES}")
message(STATUS "=====================================")
