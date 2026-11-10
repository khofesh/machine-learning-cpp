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

## Performance

Each of the ~50 `find_min_global` evaluations runs a 10-fold cross-validation. The folds are independent, so `ParallelCrossValidate()` runs them with OpenMP (`-fopenmp`); the per-fold statistics are recombined in a fixed order, so results are identical to `dlib::cross_validate_regression_trainer`. On 24 cores this cuts a run from ~21 min to ~3.8 min. Set `OMP_NUM_THREADS` to control the thread count.

