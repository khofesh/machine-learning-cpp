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
sudo dnf install -y wget
sudo dnf install -y ninja-build
sudo dnf install -y gnuplot
sudo dnf install -y vim
sudo dnf install -y python3-virtualenv  # equivalent to python3-venv


sudo dnf install ocl-icd-devel opencl-headers

sudo dnf install fmt-devel
sudo dnf install nnpack-devel

# arrayfire
sudo dnf install spdlog-devel

pip3 install pyyaml
pip3 install typing_extensions
```

### flashlight

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
  -DArrayFire_DIR=/opt/ArrayFire-3.10.0-Linux/share/ArrayFire/cmake/ \
  -DFL_ARRAYFIRE_USE_CUDA=ON -DFL_ARRAYFIRE_USE_CPU=OFF \
  -DFL_BUILD_DISTRIBUTED=OFF -DCMAKE_CUDA_ARCHITECTURES=86
```

At runtime ArrayFire's bundled `libnvrtc.so.12` needs `libnvrtc-builtins.so.12.2` from `/opt/ArrayFire-3.10.0-Linux/lib64`, which is not in the loader cache, so add it once:

```shell
echo '/opt/ArrayFire-3.10.0-Linux/lib64' | sudo tee /etc/ld.so.conf.d/arrayfire.conf
sudo ldconfig
```

Only one ArrayFire backend may be linked at a time: `FL_ARRAYFIRE_USE_CUDA=ON` requires `FL_ARRAYFIRE_USE_CPU=OFF` (and vice versa), otherwise CMake errors out.

### nccl

download the NCCL tarball for CUDA 13 from https://developer.nvidia.com/nccl and extract it to `/opt/nccl/<version>` with a `current` symlink (currently `/opt/nccl/2.27.7-cuda13.0`).

### cudnn

download the cuDNN tarball for CUDA 13 from https://developer.nvidia.com/cudnn-downloads and extract it to `/opt/cudnn/<version>` with a `current` symlink (currently `/opt/cudnn/9.12.0-cuda13`). dlib is built against `/opt/cudnn/current` (see below).

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
wget https://arrayfire.s3.amazonaws.com/3.10.0/ArrayFire-v3.10.0_Linux_x86_64.sh
chmod +x ArrayFire-v3.10.0_Linux_x86_64.sh

# https://arrayfire.org/docs/installing.htm#gsc.tab=0
sudo ./ArrayFire-v3.10.0_Linux_x86_64.sh --include-subdir --prefix=/opt
# env
echo 'export LD_LIBRARY_PATH=/opt/ArrayFire-3.10.0-Linux/lib64:$LD_LIBRARY_PATH' >> ~/.bashrc
source ~/.bashrc
# or
echo '/opt/ArrayFire-3.10.0-Linux/lib64' | sudo tee /etc/ld.so.conf.d/arrayfire.conf
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

```json
{
  "VCPKG_ROOT": "/home/fahmad/vcpkg"
}
```

packages used from vcpkg

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

# armadillo, boost serialization (mlpack samples), cpp-httplib (chapter013), fmt (tapkee)
./vcpkg install armadillo boost-serialization cpp-httplib fmt
```

### dlib (CUDA + GUI support)

vcpkg's `dlib` port has neither GUI nor CUDA, so `chapter002/img/dlib` (GUI) and `chapter004/dlib` (CUDA) use the dlib source in `development/libs/sources/dlib`, built with both and installed into `development/libs`. This is the active `DLib` step in `development/install_env.sh`:

```shell
cd development
export NVCC_PREPEND_FLAGS="-allow-unsupported-compiler"   # CUDA 13.3 vs GCC 16
FORCE_REBUILD=1 . ./install_lib.sh https://github.com/davisking/dlib v20.0.1 \
  -DCMAKE_BUILD_TYPE=Release -DDLIB_USE_CUDA=ON -DDLIB_NO_GUI_SUPPORT=OFF \
  -DCMAKE_CUDA_ARCHITECTURES=86 -DCUDNN_ROOT=/opt/cudnn/current
```

dlib requires cuDNN alongside CUDA; `FindCUDNN.cmake` in v20.0.1 locates it via `-DCUDNN_ROOT`. `homlcpp/chapter002/img/dlib` and `homlcpp/chapter004/dlib` point `dlib_DIR` at this install (`development/libs/lib64/cmake/dlib`); the other dlib examples keep using vcpkg's build.

ArrayFire ships its own cuDNN 9.8 and puts `/opt/ArrayFire-3.10.0-Linux/lib64` first in `LD_LIBRARY_PATH`, shadowing the system cuDNN 9.12 dlib links against. `chapter004/dlib` links with `--disable-new-dtags` (DT_RPATH) so it always resolves `/opt/cudnn/current/lib`.

### build notes for newer packages

- **HDF5 2.2.0** (vcpkg): use config mode (`find_package(HDF5 CONFIG REQUIRED)`) so the imported target pulls in zlib/libaec transitively. Module mode only links `libhdf5.a`, which fails with undefined `inflate`/`SZ_*` symbols.
- **mlpack 4.8**: the `mlpack::data::` namespace was removed; use `mlpack::MinMaxScaler`, `mlpack::StandardScaler` and the `DataOptions` overloads of `Load`/`Save`, e.g. `Load(file, mat, mlpack::Fatal + mlpack::Categorical)`. The `bool fatal` / `DatasetInfo&` overloads are deprecated (removed in mlpack 5).
- **Eigen 5**: `Eigen::initParallel()` is deprecated (no-op); `find_package(Eigen3)` is called without a version because Eigen 3.4's config does not accept a `3.4...5` range.
- **libtorch 2.14**: requires C++20.
- **CUDA 13.3 + GCC 16**: nvcc rejects GCC > 15 as host compiler; the root `CMakeLists.txt` appends `-allow-unsupported-compiler` to `CMAKE_CUDA_FLAGS`.
- GUI examples (`img-opencv`, `img-dlib`) are interactive; run them under `xvfb-run` for headless smoke tests.

## building and running the samples

All samples under `homlcpp/` belong to the root CMake project (chapters 001-013; chapter 014 is the Android app and is not configured here).

```shell
cmake -B build -S . -DCMAKE_BUILD_TYPE=Debug
cmake --build build --parallel
```

Eigen comes from `development/libs` (`homlcpp/CMakeLists.txt` sets `Eigen3_DIR` and turns off the CMake user package registry, because the onnxruntime build registers its bundled Eigen in `~/.cmake/packages`). If an old `build/` still points at that Eigen, reconfigure with `-UEigen3_DIR`.

Most examples take a dataset directory as the first argument:

| sample | command |
| --- | --- |
| `chapter001/*` | run with no arguments |
| `chapter002/csv/*`, `json_sample` | `data/iris.csv`, `data/reviews.json` |
| `chapter002/hdf5` | `data/reviews.json` (writes `reviews.h5`) |
| `chapter002/img/*` | an image path; interactive GUI (`img-dlib`, `img-opencv`) |
| `chapter003/*` | no arguments (writes `plot.png`) |
| `chapter004/dlib2`, `chapter004/mlpack` | `homlcpp/chapter004/data` |
| `chapter005/*` | `homlcpp/chapter005/data` |
| `chapter006/*` | `homlcpp/chapter006/data` |
| `chapter007/*` | `homlcpp/chapter007/data` (generated sample data) |
| `chapter008/eigen`, `chapter008/mlpack` | MovieLens folder with `movies.csv` and `ratings.csv` |
| `chapter009/dlib` | no arguments |
| `chapter009/mlpack` | `homlcpp/chapter009/data/wdbc.data` (UCI Breast Cancer Wisconsin) |
| `chapter010/dlib`, `chapter010/flashlight`, `chapter010/mlpack` | no arguments (synthetic data, `chapter010/data`) |
| `chapter010/pytorch` | folder with raw MNIST `*-idx1-ubyte` / `*-idx3-ubyte` files |
| `chapter012/*` (except onnx) | no arguments |
| `chapter012/onnxruntime` | `<resnet50.onnx> <synset.txt> <image>` |
| `chapter013/flashlight` | no arguments; set up an MLflow server to log metrics, otherwise it warns and continues |

Datasets used by the runs above but not committed:

- MovieLens: https://files.grouplens.org/datasets/movielens/ml-latest-small.zip
- MNIST: https://storage.googleapis.com/cvdf-datasets/mnist/
- ResNet-50 ONNX: https://github.com/onnx/models (`validated/vision/classification/resnet/model/resnet50-v1-7.onnx`) plus `synset.txt`

`chapter006/*` and `chapter008/eigen` are heavy in a `Debug` build (`-O0`); build with `-DCMAKE_BUILD_TYPE=Release` if it seems to hang.

### sentiment-pytorch (chapter 011)

`sentiment-pytorch` needs two external assets that are not in the repository:

1. A TorchScript BERT model, exported with `transformers` (writes `homlcpp/chapter011/pytorch/bert_model.pt`, ~430 MB):

```shell
python3 -m venv .venv
. .venv/bin/activate
# transformers 5.x dropped the `torchscript=` flag used by export.py
pip install "transformers<5" torch tqdm
cd homlcpp/chapter011/pytorch
python export.py
```

2. IMDB reviews in torchtext layout, i.e. `<dataset>/train/pos/*.txt` and `<dataset>/train/neg/*.txt`. Download and extract them with the helper:

```shell
env_scripts/download_sentiment_data.sh              # -> development/datasets/aclImdb
env_scripts/download_sentiment_data.sh -n 20        # + small subset for smoke tests
```

If the Stanford host is unreachable, the script falls back to the HuggingFace parquet mirror and converts it to `train/{pos,neg}` (needs `pyarrow`: `pip install pyarrow`).

`vocab.txt` (BERT cased vocabulary) is already in the repo. Run:

```shell
sentiment-pytorch /path/to/aclImdb homlcpp/chapter011/pytorch/vocab.txt homlcpp/chapter011/pytorch/bert_model.pt
```

Known open issues are tracked in [TODO.md](TODO.md).

## folder structure

```shell
tree -I "Hands-on-Machine-learning-with-C-Second-Edition|LearningModCppFinance" -L 4
```

## references

- C++ Implementation of PyTorch Tutorials for Everyone - https://github.com/prabhuomkar/pytorch-cpp
- Learning Modern C++ for Finance - https://github.com/QuantDevHacks/LearningModCppFinance/
- distrobox - https://github.com/89luca89/distrobox?tab=readme-ov-file
