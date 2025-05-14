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

pip3 install pyyaml
pip3 install typing
pip3 install typing_extensions
```

### nccl

download nccl from here https://developer.nvidia.com/nccl

```shell
sudo dnf install nccl-local-repo-rhel9-2.26.5-cuda12.9-1.0-1.x86_64.rpm
sudo dnf  install libnccl-2.26.5-1+cuda12.9 libnccl-devel-2.26.5-1+cuda12.9 libnccl-static-2.26.5-1+cuda12.9
```

## environment
