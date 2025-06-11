# Hands-on machine learning with C++ 2nd edition

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

## flashlight

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

### nccl

download nccl from here https://developer.nvidia.com/nccl

```shell
sudo dnf install nccl-local-repo-rhel9-2.26.5-cuda12.9-1.0-1.x86_64.rpm
sudo dnf  install libnccl-2.26.5-1+cuda12.9 libnccl-devel-2.26.5-1+cuda12.9 libnccl-static-2.26.5-1+cuda12.9
```

### pytorch

down the zip file here https://pytorch.org/get-started/locally/

or https://download.pytorch.org/libtorch/cu128/libtorch-cxx11-abi-shared-with-deps-2.7.0%2Bcu128.zip

```shell
wget https://download.pytorch.org/libtorch/cu128/libtorch-cxx11-abi-shared-with-deps-2.7.0%2Bcu128.zip
mv libtorch-cxx11-abi-shared-with-deps-2.7.0+cu128.zip development/libs
cd development/libs
unzip libtorch-cxx11-abi-shared-with-deps-2.7.0+cu128.zip
```

I'm using cuda 12.9, so pay attention to this PR https://github.com/pytorch/pytorch/issues/152756 and make some changes accordingly

run `check_torch` if the lib is working

### arrayfire

download arrayfire here https://arrayfire.com/binaries/

```shell
cd development
mkdir arrayfire
wget https://arrayfire.gateway.scarf.sh/linux/3.9.0/ArrayFire.sh
chmod +x ArrayFire-v3.9.0_Linux_x86_64.sh

./ArrayFire-v3.9.0_Linux_x86_64.sh

# say "no" during
## Do you accept the license? [yn]:
## y
## By default the ArrayFire will be installed in:
##   "/path/to/development/arrayfire/ArrayFire-3.9.0-Linux"
## Do you want to include the subdirectory ArrayFire-3.9.0-Linux?
## Saying no will install in: "/path/to/development/arrayfire" [Yn]:
##
```

### dlib

I got frustrated with this, so I use vcpkg

```shell
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg

./bootstrap-vcpkg.sh  # on linux
./vcpkg install dlib
```

### chapter 2

```shell
# cd to your vcpkg
./vcpkg install nlohmann-json
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
