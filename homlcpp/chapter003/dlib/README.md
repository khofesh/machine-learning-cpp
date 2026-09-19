# chapter003 / dlib

Grid search over an SVR polynomial kernel with `dlib::find_min_global`, then plots the fit with plotcpp.

## Build

From the repo root:

```bash
cmake -B build -S . -DCMAKE_BUILD_TYPE=Debug
cmake --build build --target grid-dlib
```

## Run

```bash
./build/homlcpp/chapter003/dlib/grid-dlib
```

Writes `plot.png` (gnuplot) in the current directory.
