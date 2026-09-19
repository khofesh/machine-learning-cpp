# chapter003 / flashlight

Polynomial regression trained with flashlight autograd, then plots the fit with plotcpp.

## Build

From the repo root:

```bash
cmake -B build -S . -DCMAKE_BUILD_TYPE=Debug
cmake --build build --target grid_fl
```

Requires flashlight from `development/libs` and ArrayFire from `/opt` (wired in `CMakeLists.txt`). The local flashlight install is built with the ArrayFire CUDA backend; see the "flashlight (CUDA 13)" section in the root `README.md` to rebuild it.

## Run

If `/opt/ArrayFire-3.9.0-Linux/lib64` is not in the loader cache, prefix the run with `LD_LIBRARY_PATH=/opt/ArrayFire-3.9.0-Linux/lib64:$LD_LIBRARY_PATH` (or add it to `/etc/ld.so.conf.d/arrayfire.conf` once):

```bash
./build/homlcpp/chapter003/flashlight/grid_fl <polynomial_degree> <learning_rate> <batch_size>
```

Example (the book's tuned values):

```bash
./build/homlcpp/chapter003/flashlight/grid_fl 14 0.045 1000
```

Writes `plot_<degree>_<learning_rate>_<batch_size>.png` (gnuplot) in the current directory.

With the CUDA backend `14 0.045 32` takes ~12 s instead of several minutes on CPU. `batch_size 32` with `degree 14` can train to `nan`; use `14 0.045 1000` for a stable fit. `degree 1` currently hits an `fl::Shape::dim` bounds error in flashlight `main` (a 1-D shape is produced before training).
