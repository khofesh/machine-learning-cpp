# Hands-on machine learning with C++ 2nd edition

## cuda version on local

```shell
$ nvcc --version
nvcc: NVIDIA (R) Cuda compiler driver
Copyright (c) 2005-2026 NVIDIA Corporation
Built on Tue_Jun_09_02:43:40_PM_PDT_2026
Cuda compilation tools, release 13.3, V13.3.73
Build cuda_13.3.r13.3/compiler.38244171_0
```

## local development environment

installing several dependencies

```shell
# Basic tools and development packages
sudo dnf install -y unzip
sudo dnf install -y gcc gcc-c++ make  # equivalent to build-essential
sudo dnf install -y gdb
sudo dnf install -y git
sudo dnf install -y cmake
sudo dnf install -y cmake-gui  # equivalent to cmake-curses-gui
sudo dnf install -y python3
sudo dnf install -y python3-pip
sudo dnf install -y blas-devel  # equivalent to libblas-dev
sudo dnf install -y openblas-devel  # equivalent to libopenblas-dev
sudo dnf install -y fftw-devel  # equivalent to libfftw3-dev
sudo dnf install -y atlas-devel  # equivalent to libatlas-base-dev
sudo dnf install -y lapack-devel  # equivalent to liblapack-dev and liblapacke-dev
sudo dnf install -y boost-devel  # equivalent to libboost-all-dev

# OpenCV packages - these may need adjustment based on version available in repos
sudo dnf install -y opencv-core  # equivalent to libopencv-core4.5d
sudo dnf install -y opencv-devel # development files
sudo dnf install -y opencv  # main package

# Additional libraries
sudo dnf install -y hdf5-devel  # equivalent to libhdf5-dev
sudo dnf install -y json-c-devel  # equivalent to libjson-c-dev
sudo dnf install -y libX11-devel  # equivalent to libx11-dev
sudo dnf install -y java-1.8.0-openjdk-devel  # equivalent to openjdk-8-jdk
sudo dnf install -y wget
sudo dnf install -y ninja-build
sudo dnf install -y gnuplot
sudo dnf install -y vim
sudo dnf install -y python3-virtualenv  # equivalent to python3-venv


sudo dnf install ocl-icd-devel opencl-headers

sudo dnf install fmt-devel
sudo dnf install nnpack-devel
sudo dnf install mlpack-devel

# arrayfire
sudo dnf install spdlog-devel

pip3 install pyyaml
pip3 install typing
pip3 install typing_extensions
```

### flashlight

```shell
cat > flashlight_algo_fix.patch << 'EOF'
diff --git a/flashlight/fl/tensor/backend/af/ArrayFireReductions.cpp b/flashlight/fl/tensor/backend/af/ArrayFireReductions.cpp
index xxxxxxx..xxxxxxx 100644
--- a/flashlight/fl/tensor/backend/af/ArrayFireReductions.cpp
+++ b/flashlight/fl/tensor/backend/af/ArrayFireReductions.cpp
@@ -13,6 +13,7 @@
 #include "flashlight/fl/tensor/backend/af/ArrayFireTensor.h"

 #include <stdexcept>
+#include <algorithm>

 #include "flashlight/fl/tensor/Index.h"
 #include "flashlight/fl/tensor/backend/af/Utils.h"
diff --git a/flashlight/fl/tensor/TensorBase.cpp b/flashlight/fl/tensor/TensorBase.cpp
index xxxxxxx..xxxxxxx 100644
--- a/flashlight/fl/tensor/TensorBase.cpp
+++ b/flashlight/fl/tensor/TensorBase.cpp
@@ -10,6 +10,7 @@
 #include "flashlight/fl/tensor/TensorBase.h"

 #include <cstring>
+#include <algorithm>
 #include <memory>
 #include <numeric>
 #include <sstream>
EOF

cd /media/wdhome/github/khofesh/machine-learning-cpp/development/libs/sources/flashlight/
patch -p1 < /path/to/flashlight_algo_fix.patch
```

### flashlight (CUDA 13)

`main` (commit `439bb526`, "Fix CUDA 13 nvToolsExt build break") builds with CUDA 13.3 through ArrayFire's CUDA backend. The GCC 16 host compiler still needs a few fixes; they are kept as `development/flashlight_main_cuda.patch`:

- `CMakeLists.txt`: `CMAKE_CXX_STANDARD 17` -> `20` (`std::unordered_map::contains`)
- `cmake/flashlightConfig.cmake.in`: `find_dependency(CUDAToolkit)` so consumers get `CUDA::cublas`
- `TensorBase.h`: add `<cstdint>` (GCC 16 no longer includes it transitively)
- `backend/jit/ShapeInference.cpp`: add `<algorithm>` for `std::reverse`

Build/install (NVCC 13.3 rejects GCC > 15, hence `NVCC_PREPEND_FLAGS`; this also applies to CMake's CUDA compiler detection, where `CMAKE_CUDA_FLAGS` is not used):

```shell
cd development
patch -p1 -d libs/sources/flashlight < flashlight_main_cuda.patch   # if starting fresh
export NVCC_PREPEND_FLAGS="-allow-unsupported-compiler"
FORCE_REBUILD=1 . ./install_lib.sh https://github.com/flashlight/flashlight.git main \
  -DFL_BUILD_TESTS=OFF -DFL_BUILD_EXAMPLES=OFF \
  -DFL_USE_CUDA=ON -DFL_USE_CPU=OFF -DFL_USE_ONEDNN=OFF \
  -DArrayFire_DIR=/opt/ArrayFire-3.9.0-Linux/share/ArrayFire/cmake/ \
  -DFL_ARRAYFIRE_USE_CUDA=ON -DFL_ARRAYFIRE_USE_CPU=OFF \
  -DFL_BUILD_DISTRIBUTED=OFF -DCMAKE_CUDA_ARCHITECTURES=86
```

At runtime ArrayFire's bundled `libnvrtc.so.12` needs `libnvrtc-builtins.so.12.2` from `/opt/ArrayFire-3.9.0-Linux/lib64`, which is not in the loader cache, so add it once:

```shell
echo '/opt/ArrayFire-3.9.0-Linux/lib64' | sudo tee /etc/ld.so.conf.d/arrayfire.conf
sudo ldconfig
```

Only one ArrayFire backend may be linked at a time: `FL_ARRAYFIRE_USE_CUDA=ON` requires `FL_ARRAYFIRE_USE_CPU=OFF` (and vice versa), otherwise CMake errors out.

### nccl

download nccl from here https://developer.nvidia.com/nccl

```shell
# adjust the +cudaXX suffix to match the installed toolkit (CUDA 13.3 here)
sudo dnf install nccl-local-repo-rhel9-2.26.5-cuda12.9-1.0-1.x86_64.rpm
sudo dnf  install libnccl-2.26.5-1+cuda12.9 libnccl-devel-2.26.5-1+cuda12.9 libnccl-static-2.26.5-1+cuda12.9
```

### pytorch

down the zip file here https://pytorch.org/get-started/locally/

or https://download.pytorch.org/libtorch/cu132/libtorch-shared-with-deps-2.14.0%2Bcu132.zip

```shell
wget https://download.pytorch.org/libtorch/cu132/libtorch-shared-with-deps-2.14.0%2Bcu132.zip
mv libtorch-shared-with-deps-2.14.0+cu132.zip development/libs
cd development/libs
unzip libtorch-shared-with-deps-2.14.0+cu132.zip
```

libtorch 2.14 requires C++20 (`check_torch` is built with `CXX_STANDARD 20`). CUDA 13.3 rejects GCC > 15 as host compiler, so the root `CMakeLists.txt` adds `-allow-unsupported-compiler` to `CMAKE_CUDA_FLAGS`.

run `check_torch` if the lib is working

### arrayfire

download arrayfire here https://arrayfire.com/binaries/

```shell
cd development
mkdir arrayfire
wget https://arrayfire.s3.amazonaws.com/3.10.0/ArrayFire-v3.10.0_Linux_x86_64.sh
chmod +x ArrayFire-v3.10.0_Linux_x86_64.sh

# https://arrayfire.org/docs/installing.htm#gsc.tab=0
sudo ./ArrayFire-v3.10.0_Linux_x86_64.sh --include-subdir --prefix=/opt
# env
echo 'export LD_LIBRARY_PATH=/opt/ArrayFire-3.9.0-Linux/lib64:$LD_LIBRARY_PATH' >> ~/.bashrc
source ~/.bashrc
# or
sudo echo '/opt/ArrayFire-3.9.0-Linux/lib64' | sudo tee /etc/ld.so.conf.d/arrayfire.conf
sudo ldconfig
```

### vcpkg

```shell
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg

./bootstrap-vcpkg.sh  # on linux
./vcpkg install dlib
```

VS Code Settings

1. Open VS Code settings (Ctrl+, or Cmd+,)
2. Search for "cmake configure environment"
3. Add the environment variable in CMake: Configure Environment:

```
json{
  "VCPKG_ROOT": "/home/fahmad/vcpkg"
}
```

chapter 2

```shell
# cd to your vcpkg
cd /to/your/path
# optional
./vcpkg upgrade --no-dry-run

# json
./vcpkg install nlohmann-json

# fast-cpp-csv-parser
./vcpkg install fast-cpp-csv-parser

# mlpack
./vcpkg install mlpack

# HighFive
./vcpkg install highfive

# hdf5
./vcpkg install hdf5
```

### dlib (GUI support)

vcpkg's `dlib` port is built with `DLIB_NO_GUI_SUPPORT=ON`, so the GUI example (`chapter002/img/dlib`) cannot link. Build the bundled dlib source with X11 GUI support and install it into `development/libs`:

```shell
cmake -S development/libs/sources/dlib -B development/libs/sources/dlib/build \
  -DCMAKE_BUILD_TYPE=Release \
  -DDLIB_NO_GUI_SUPPORT=OFF \
  -DBUILD_SHARED_LIBS=OFF \
  -DCMAKE_INSTALL_PREFIX=$PWD/development/libs
cmake --build development/libs/sources/dlib/build --parallel
cmake --install development/libs/sources/dlib/build
```

`homlcpp/chapter002/img/dlib/CMakeLists.txt` points `dlib_DIR` at this install (`development/libs/lib64/cmake/dlib`); the other dlib examples keep using vcpkg's build.

### build notes for newer packages

- **HDF5 2.2.0** (vcpkg): use config mode (`find_package(HDF5 CONFIG REQUIRED)`) so the imported target pulls in zlib/libaec transitively. Module mode only links `libhdf5.a`, which fails with undefined `inflate`/`SZ_*` symbols.
- **mlpack 4.8**: the `mlpack::data::` namespace was removed; use `mlpack::DatasetInfo`, `mlpack::Load`, `mlpack::MinMaxScaler`, `mlpack::StandardScaler`.
- **libtorch 2.14**: requires C++20.
- **CUDA 13.3 + GCC 16**: nvcc rejects GCC > 15 as host compiler; the root `CMakeLists.txt` appends `-allow-unsupported-compiler` to `CMAKE_CUDA_FLAGS`.
- GUI examples (`img-opencv`, `img-dlib`) are interactive; run them under `xvfb-run` for headless smoke tests.

**I haven't succeeded in installing flashlight-cuda or flashlight-cpu using vcpkg, this is the steps I've tried**

https://www.if-not-true-then-false.com/2024/install-nvidia-cudnn-on-fedora/

```shell
mkdir cudnn
cd cudnn
wget https://developer.download.nvidia.com/compute/cudnn/redist/cudnn/linux-x86_64/cudnn-linux-x86_64-9.10.2.21_cuda12-archive.tar.xz # https://developer.nvidia.com/cudnn-downloads?target_os=Linux&target_arch=x86_64&Distribution=Agnostic&cuda_version=12
tar xvf cudnn-linux-x86_64-9.10.2.21_cuda12-archive.tar.xz
cd cudnn-linux-x86_64-9.10.2.21_cuda12-archive
# pick the archive matching your toolkit (cuda13 for CUDA 13.3); /usr/local/cuda points at the active one
sudo cp include/cudnn*.h /usr/local/cuda/include/
sudo cp lib/libcudnn* /usr/local/cuda/lib64/
sudo chmod a+r /usr/local/cuda/include/cudnn*.h /usr/local/cuda/lib64/libcudnn*
export ArrayFire_DIR=/media/wdhome/github/khofesh/machine-learning-cpp/development/arrayfire
export LD_LIBRARY_PATH=/media/wdhome/github/khofesh/machine-learning-cpp/development/arrayfire/lib64:$LD_LIBRARY_PATH
export CXXFLAGS="-Wno-template-id-cdtor"
export CFLAGS="-Wno-template-id-cdtor"
cd ~/vcpkg
./vcpkg install flashlight-cuda

# flashlight cpu

```

## folder structure

```shell
tree -I "Hands-on-Machine-learning-with-C-Second-Edition|LearningModCppFinance" -L 4
```

## references

- C++ Implementation of PyTorch Tutorials for Everyone - https://github.com/prabhuomkar/pytorch-cpp
- Learning Modern C++ for Finance - https://github.com/QuantDevHacks/LearningModCppFinance/
- distrobox - https://github.com/89luca89/distrobox?tab=readme-ov-file

## TODO

- [ ] use vcpkg
