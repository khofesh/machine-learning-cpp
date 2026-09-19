# chapter003 / mlpack

Grid search over `LinearRegression` regularization (`HyperParameterTuner` + `SimpleCV`), then plots the fit with plotcpp.

## Build

From the repo root:

```bash
cmake -B build -S . -DCMAKE_BUILD_TYPE=Debug
cmake --build build --target grid-mlpack
```

Uses the vcpkg mlpack (4.8) via the local `cmake/Findmlpack.cmake` module and Armadillo.

## Run

```bash
./build/homlcpp/chapter003/mlpack/grid-mlpack
```

Prints the best lambda and writes `plot.png` (gnuplot) in the current directory.
