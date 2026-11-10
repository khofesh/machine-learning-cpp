# TODO

No open issues.

Resolved 2026-11-10:

- `chapter004/mlpack` (`mlpack-cluster`): the empty plot was `dataset5.csv` + DBSCAN, not a parameter bug. `dataset5` is a uniform blob with no density structure (even the 15th-nearest-neighbour distance is >= 0.13, above `epsilon 0.1`), so DBSCAN legitimately labels every point as noise. The plot code now skips empty cluster sets instead of emitting a bare `plot` command, and DBSCAN noise points are drawn in gray.
- `chapter011/pytorch` (`sentiment-pytorch`) runs against the current libs with `bert_model.pt` and `development/datasets/aclImdb` (training started, loss/accuracy printed). `chapter012/onnxruntime` (`onnx-load`) runs with `resnet50-v1-7.onnx` + `synset.txt` and classifies a test image; see README.md for the download commands.
- `chapter006/*` and `chapter008/eigen` now build with `-Og` in `Debug` (`dlib-dr` 27 s, `tapkee-dr` 13 s on the chapter 006 data).
- Eigen in `development/libs` is 5.0.1 again (the version pinned in `env_scripts/install_env.sh`); the full project builds and the Eigen/tapkee/mlpack samples run against it.
