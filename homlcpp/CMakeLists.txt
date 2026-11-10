# shared paths for the chapter samples
set(LIBS_DIR ${CMAKE_SOURCE_DIR}/development/libs)
set(PLOTCPP_PATH ${LIBS_DIR}/sources/plotcpp CACHE PATH "path to plotcpp sources dir")
set(CSV_LIB_PATH ${LIBS_DIR}/sources/fast-cpp-csv-parser CACHE PATH "path to fast-cpp-csv-parser include dir")
set(TAPKEE_PATH ${LIBS_DIR}/include/tapkee CACHE PATH "path to tapkee install include dir")

# ArrayFire is used from /opt by both the direct samples and flashlight
set(ARRAYFIRE_ROOT /opt/ArrayFire-3.10.0-Linux)
list(PREPEND CMAKE_PREFIX_PATH ${ARRAYFIRE_ROOT})

if(NOT MLPACK_INCLUDE_DIR)
  find_path(MLPACK_INCLUDE_DIR NAMES mlpack/core.hpp)
endif()

# Eigen is installed under development/libs; ignore ~/.cmake/packages entries
# (e.g. onnxruntime's bundled Eigen registers itself there)
set(CMAKE_FIND_USE_PACKAGE_REGISTRY OFF)
if(EXISTS ${LIBS_DIR}/share/eigen3/cmake/Eigen3Config.cmake)
  set(Eigen3_DIR ${LIBS_DIR}/share/eigen3/cmake CACHE PATH "Eigen3 config dir" FORCE)
endif()

# onnxruntime is installed under development/libs; make its config discoverable
if(NOT onnxruntime_DIR AND EXISTS ${LIBS_DIR}/lib64/cmake/onnxruntime/onnxruntimeConfig.cmake)
  set(onnxruntime_DIR ${LIBS_DIR}/lib64/cmake/onnxruntime CACHE PATH "onnxruntime config dir")
endif()

add_subdirectory(chapter001)
add_subdirectory(chapter002)
add_subdirectory(chapter003)
add_subdirectory(chapter004)
add_subdirectory(chapter005)
add_subdirectory(chapter006)
add_subdirectory(chapter007)
add_subdirectory(chapter008)
add_subdirectory(chapter009)
add_subdirectory(chapter010)
add_subdirectory(chapter011)
add_subdirectory(chapter012)
add_subdirectory(chapter013)
