#!/usr/bin/env bash
set -x
set -e

DEV_DIR=$(pwd)

mkdir -p libs
mkdir -p libs/sources

# Blaze
. ./install_lib.sh https://bitbucket.org/blaze-lib/blaze.git v3.8.2

# Firearray
. ./install_lib.sh https://github.com/arrayfire/arrayfire v3.10.0 -DBUILD_TESTING=OFF -DAF_BUILD_EXAMPLES=OFF

# Flashlight
. ./install_lib.sh https://github.com/flashlight/flashlight.git v0.4.0 -DFL_BUILD_TESTS=OFF -DFL_BUILD_EXAMPLES=OFF -DFL_LIBRARIES_USE_MKL=OFF -DFL_USE_CPU=ON  -DFL_USE_ONEDNN=OFF -DArrayFire_DIR=/development/libs/share/ArrayFire/cmake/ -DFL_ARRAYFIRE_USE_CPU=ON -DFL_BUILD_DISTRIBUTED=OFF

# DLib
. ./install_lib.sh https://github.com/davisking/dlib v20.0.1

# Armadillo
. ./install_lib.sh https://gitlab.com/conradsnicta/armadillo-code 15.6.x

# xtl
. ./install_lib.sh https://github.com/xtensor-stack/xtl 0.8.2

# xtensor
. ./install_lib.sh https://github.com/xtensor-stack/xtensor 0.27.1

# xtensor-blas
. ./install_lib.sh https://github.com/xtensor-stack/xtensor-blas 0.23.0

# NlohmanJson
. ./install_lib.sh https://github.com/nlohmann/json.git v3.12.0 -DJSON_BuildTests=OFF

# mlpack
. ./install_lib.sh https://github.com/mlpack/mlpack 4.8.0 -DBUILD_PYTHON_BINDINGS=OFF -DBUILD_TESTS=OFF -DDOWNLOAD_DEPENDENCIES=ON

# Eigen
. ./install_lib.sh https://gitlab.com/libeigen/eigen.git 5.0.1

# HighFive
. ./install_lib.sh https://github.com/BlueBrain/HighFive v2.10.1

# cpp-httplib
. ./install_lib.sh https://github.com/yhirose/cpp-httplib v0.65.0

# PlotCpp
. ./checkout_lib.sh https://github.com/Kolkir/plotcpp c86bd4f5d9029986f0d5f368450d79f0dd32c7e4

# fast-cpp-csv-parser
. ./checkout_lib.sh https://github.com/ben-strasser/fast-cpp-csv-parser 574a9fe4d323ba63416877a4a5fe59088d37aa34

# tapkee
. ./install_lib.sh https://github.com/lisitsyn/tapkee v1.4.0 -DBUILD_TESTS=OFF

# onnxruntime
. ./install_lib_custom.sh https://github.com/Microsoft/onnxruntime.git v1.31.1 "./build.sh --config RelWithDebInfo --build_shared_lib --parallel --compile_no_warning_as_error --skip_submodule_sync --allow_running_as_root --skip_tests --cmake_extra_defines CMAKE_INSTALL_PREFIX=/development/libs/ --cmake_extra_defines nnxruntime_BUILD_UNIT_TESTS=OFF --target install"

# PyTorch - install after onnxruntime to fix protobuf conflict
. ./install_lib.sh https://github.com/pytorch/pytorch v2.15.0 -DBUILD_PYTHON=OFF 

# return back
cd $DEV_DIR


