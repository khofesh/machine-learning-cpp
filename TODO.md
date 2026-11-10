# TODO

- [ ] `chapter004/mlpack` (`mlpack-cluster`): one of the cluster plots comes out empty, and gnuplot prints `plot` / `function to plot expected`. Probably DBSCAN (`epsilon 0.1`, `min_points 15`) marks every point of one dataset as noise, so nothing gets plotted. Not yet confirmed which dataset or plot it is.
- [ ] `chapter011/pytorch` (`sentiment-pytorch`) and `chapter012/onnxruntime` (`onnx-load`) are built but have not been run against the updated libs, because the BERT TorchScript model and the ResNet-50 ONNX model are not in the repo (see "building and running the samples" in README.md).
- [ ] `chapter006/*` and `chapter008/eigen` take minutes in a `Debug` build; use `Release` for quick runs.
- [ ] The installed Eigen in `development/libs` is still 3.4.0, while `env_scripts/install_env.sh` pins 5.0.1. The CMake files accept either version (no version in `find_package(Eigen3)`), but the samples have only been built against 3.4.0.
