# Graph Report - machine-learning-cpp  (2026-11-10)

## Corpus Check
- 108 files · ~184,217 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 51 file(s) not represented in the graph (top: .csv 16, .xml 12, .cmake 8)

## Summary
- 823 nodes · 1303 edges · 69 communities (34 shown, 35 thin omitted)
- Extraction: 96% EXTRACTED · 4% INFERRED · 0% AMBIGUOUS · INFERRED: 47 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `7cf22ebc`
- Run `git rev-parse HEAD` and compare to check if the graph is stale.
- Run `graphify update .` after code changes (no API cost).

## Community Hubs (Navigation)
- ReviewsHandler
- knn_kernel
- dlib-anomaly.cc
- Paper
- local development environment
- mlpack-cluster.cc
- CLAUDE.md
- install_env.sh
- dlib-cluster.cc
- env_scripts/README.md
- install_android.sh
- grid-dlib.cc
- run_container.sh
- homlcpp/README.md
- machine-learning-cpp — agent instructions
- generate_data
- imdbreader.cc
- objective
- chapter003 / flashlight
- chapter003 / mlpack
- linreg_dlib.cpp
- YOLO
- vector
- eigen_recommender.cc
- isolation-forest.h
- MNISTDataset
- ObjectDetector
- mlpack_ensemble.cc
- onnxruntime/main.cc
- iostream
- dlib-save.cc
- MainActivity.kt
- detector.cpp
- ModelImpl
- dlib-dr.cc
- NetImpl
- fl_classify.cc
- download_sentiment_data.sh
- Review
- json.cc
- Java_com_example_objectdetection_MainActivity_initObjectDetection
- create_chapters.sh
- GenerateData

## God Nodes (most connected - your core abstractions)
1. `ObjectDetector` - 41 edges
2. `ReviewsHandler` - 26 edges
3. `YOLO` - 16 edges
4. `MNISTDataset` - 16 edges
5. `Node` - 13 edges
6. `MLFlow` - 13 edges
7. `Review` - 12 edges
8. `ModelImpl` - 11 edges
9. `FoldStats` - 10 edges
10. `YOLOResult` - 10 edges

## Surprising Connections (you probably didn't know these)
- `Performance` --references--> `ParallelCrossValidate()`  [INFERRED]
  homlcpp/chapter003/dlib/README.md → homlcpp/chapter003/dlib/grid-dlib.cc
- `main()` --calls--> `inputs`  [INFERRED]
  homlcpp/chapter007/flashlight/fl_classify.cc → homlcpp/chapter009/mlpack/stacking.cc
- `main()` --calls--> `GenerateData()`  [INFERRED]
  homlcpp/chapter010/dlib/mlp-dlib.cc → homlcpp/chapter009/dlib/dlib_ensemble.cc
- `main()` --calls--> `GenerateData()`  [INFERRED]
  homlcpp/chapter010/flashlight/mlp_fl.cc → homlcpp/chapter009/dlib/dlib_ensemble.cc
- `main()` --calls--> `GenerateData()`  [INFERRED]
  homlcpp/chapter010/mlpack/mlp_mlpack.cc → homlcpp/chapter010/data/data.cc

## Import Cycles
- None detected.

## Communities (69 total, 35 thin omitted)

### Community 0 - "ReviewsHandler"
Cohesion: 0.11
Nodes (6): ReviewsHandler, error_, paper_, papers_, review_, state_

### Community 1 - "knn_kernel"
Cohesion: 0.13
Nodes (8): fill_values(), main(), read_row_help(), load_dataset(), main(), knn_kernel, edges_, samples_

### Community 2 - "dlib-anomaly.cc"
Cohesion: 0.35
Nodes (7): CombineDatasets(), IsolationForest(), LoadDataset(), main(), MultivariateGaussianDist(), OneClassSvm(), PlotClusters()

### Community 3 - "Paper"
Cohesion: 0.22
Nodes (4): Paper, id, preliminary_decision, reviews

### Community 4 - "local development environment"
Cohesion: 0.12
Nodes (15): arrayfire, build notes for newer packages, building and running the samples, cuda version on local, dlib (CUDA + GUI support), flashlight, flashlight (CUDA 13), folder structure (+7 more)

### Community 5 - "mlpack-cluster.cc"
Cohesion: 0.12
Nodes (8): DoDBScanClustering(), DoGMMClustering(), DoKMeansClustering(), DoMeanShiftClustering(), main(), PlotClusters(), main(), make_model()

### Community 7 - "install_env.sh"
Cohesion: 0.25
Nodes (4): checkout_lib.sh script, install_env.sh script, install_lib_custom.sh script, install_lib.sh script

### Community 8 - "dlib-cluster.cc"
Cohesion: 0.07
Nodes (17): DoGraphClustering(), DoGraphNewmanClustering(), DoHierarhicalClustering(), DoKMeansClustering(), DoSpectralClustering(), main(), PlotClusters(), ImdbDataset (+9 more)

### Community 9 - "env_scripts/README.md"
Cohesion: 0.33
Nodes (5): Building development environment, Building development environment with Docker, Building local development environment, Configure you GitHub account first, List of all third-party libraries

### Community 10 - "install_android.sh"
Cohesion: 0.40
Nodes (4): ANDROID_ABI, ANDROID_NDK, ANDROID_STL_SHARED, install_android.sh script

### Community 11 - "grid-dlib.cc"
Cohesion: 0.06
Nodes (26): FoldStats, n, sum_abs_err, sum_abs_err_sq, sum_sq_err, sum_x, sum_xx, sum_xy (+18 more)

### Community 21 - "machine-learning-cpp — agent instructions"
Cohesion: 0.20
Nodes (9): ast-grep, Build, Code Style, Context Retrieval Policy, graphify, Layout, machine-learning-cpp — agent instructions, Response Style (+1 more)

### Community 23 - "generate_data"
Cohesion: 0.53
Nodes (3): generate_data(), main(), make_samples_polynomial()

### Community 24 - "imdbreader.cc"
Cohesion: 0.19
Nodes (5): ImdbReader, ImdbReader::ImdbReader(), max_size_, neg_samples_, pos_samples_

### Community 26 - "chapter003 / flashlight"
Cohesion: 0.50
Nodes (3): Build, chapter003 / flashlight, Run

### Community 27 - "chapter003 / mlpack"
Cohesion: 0.50
Nodes (3): Build, chapter003 / mlpack, Run

### Community 32 - "YOLO"
Cohesion: 0.06
Nodes (22): DensityEstimationTree(), KernelDensityEstimation(), LoadDataset(), main(), MultivariateGaussianDist(), PlotClusters(), IOU(), mat2tensor() (+14 more)

### Community 33 - "vector"
Cohesion: 0.14
Nodes (4): GenerateData(), main(), GenerateData(), main()

### Community 35 - "eigen_recommender.cc"
Cohesion: 0.05
Nodes (19): gaussian_kernel_callback, gamma, main(), Plot3DData(), PlotClusters(), Reduction(), read_data(), KRRClassification() (+11 more)

### Community 36 - "isolation-forest.h"
Cohesion: 0.09
Nodes (18): CalcC(), DatasetRange, dataset, indices, IsolationForest, c, rand_engine, trees (+10 more)

### Community 37 - "MNISTDataset"
Cohesion: 0.09
Nodes (11): main(), show_pytorch_version(), CvImageToTensor(), MNISTDataset, columns_, device_, images_, labels_ (+3 more)

### Community 38 - "ObjectDetector"
Cohesion: 0.07
Nodes (16): ObjectDetector, android_app_, camera_device_, camera_id_, camera_mgr_, capture_request_, capture_session_, height_ (+8 more)

### Community 39 - "mlpack_ensemble.cc"
Cohesion: 0.10
Nodes (16): LRClassification(), main(), PlotClasses(), SMRClassification(), SVMClassification(), ABClassification(), ConvertToCSV(), DTClassification() (+8 more)

### Community 40 - "onnxruntime/main.cc"
Cohesion: 0.27
Nodes (5): main(), read_classes(), read_image(), show_model_info(), show_output()

### Community 41 - "iostream"
Cohesion: 0.12
Nodes (10): main(), make_dataset(), check_result(), handle_result(), log_param(), MLFlow, enabled_, experiment_id_ (+2 more)

### Community 42 - "dlib-save.cc"
Cohesion: 0.56
Nodes (6): func(), LoadAndPredictKRR(), LoadAndPredictNetwork(), main(), TrainAndSaveKRR(), TrainAndSaveNetwork()

### Community 44 - "detector.cpp"
Cohesion: 0.18
Nodes (5): onDisconnected(), onError(), onSessionActive(), onSessionClosed(), onSessionReady()

### Community 46 - "ModelImpl"
Cohesion: 0.07
Nodes (10): LeNet5Impl, conv_, full_, export_model(), tokenize(), ModelImpl, bert_, dropout_ (+2 more)

### Community 47 - "dlib-dr.cc"
Cohesion: 0.23
Nodes (7): LDAReduction(), main(), PCACompression(), PCAReduction(), PlotClusters(), SammonReduction(), labels

### Community 49 - "NetImpl"
Cohesion: 0.19
Nodes (6): func(), main(), NetImpl, l1_, l2_, l3_

### Community 50 - "fl_classify.cc"
Cohesion: 0.33
Nodes (7): apply_classifier(), load_dataset(), main(), make_kernel_matrix(), PlotClasses(), train_kernel_classifier(), train_linear_classifier()

### Community 51 - "download_sentiment_data.sh"
Cohesion: 0.67
Nodes (5): download(), download_archive(), download_huggingface(), download_sentiment_data.sh script, usage()

### Community 52 - "Review"
Cohesion: 0.20
Nodes (9): Review, confidence, evaluation, id, language, orientation, remarks, text (+1 more)

### Community 56 - "json.cc"
Cohesion: 0.43
Nodes (3): main(), main(), ReadPapersReviews()

## Knowledge Gaps
- **88 isolated node(s):** `error_`, `paper_`, `papers_`, `review_`, `state_` (+83 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 358 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **35 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `ObjectDetector` connect `ObjectDetector` to `YOLO`, `detector.cpp`, `native-lib.cpp`, `.process_image`?**
  _High betweenness centrality (0.068) - this node is a cross-community bridge._
- **What connects `error_`, `paper_`, `papers_` to the rest of the system?**
  _88 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `ReviewsHandler` be split into smaller, more focused modules?**
  _Cohesion score 0.1111111111111111 - nodes in this community are weakly interconnected._
- **Why does `ReviewsHandler` connect `ReviewsHandler` to `Paper`, `Review`, `.number_float`, `json.cc`, `.parse_error`?**
  _High betweenness centrality (0.052) - this node is a cross-community bridge._
- **Should `knn_kernel` be split into smaller, more focused modules?**
  _Cohesion score 0.12554112554112554 - nodes in this community are weakly interconnected._
- **Why does `Paper` connect `Paper` to `ReviewsHandler`, `vector`, `Review`?**
  _High betweenness centrality (0.046) - this node is a cross-community bridge._
- **Should `local development environment` be split into smaller, more focused modules?**
  _Cohesion score 0.125 - nodes in this community are weakly interconnected._