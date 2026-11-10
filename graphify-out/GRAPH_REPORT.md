# Graph Report - machine-learning-cpp  (2026-11-10)

## Corpus Check
- 109 files · ~184,424 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 51 file(s) not represented in the graph (top: .csv 15, .xml 12, .cmake 8)

## Summary
- 882 nodes · 1431 edges · 61 communities (31 shown, 30 thin omitted)
- Extraction: 96% EXTRACTED · 4% INFERRED · 0% AMBIGUOUS · INFERRED: 52 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `ca0b1123`
- Run `git rev-parse HEAD` and compare to check if the graph is stale.
- Run `graphify update .` after code changes (no API cost).

## Community Hubs (Navigation)
- ReviewsHandler
- fl_classify.cc
- dlib-anomaly.cc
- grid_fl.cc
- local development environment
- mlpack-cluster.cc
- CLAUDE.md
- install_env.sh
- string
- env_scripts/README.md
- install_android.sh
- grid-dlib.cc
- dlib-cluster.cc
- run_container.sh
- tapkee-dr.cc
- ModelImpl
- filesystem
- GenerateData
- homlcpp/README.md
- machine-learning-cpp — agent instructions
- search_optuna.py
- chapter003 / flashlight
- chapter003 / mlpack
- linreg_eigen.cpp
- core
- dlib-save.cc
- YOLO
- export.py
- eigen_recommender.cc
- isolation-forest.h
- MNISTDataset
- ObjectDetector
- mlpack-classify.cc
- MLFlow
- iostream
- MainActivity.kt
- detector.cpp
- NetImpl
- dlib-dr.cc
- random
- download_sentiment_data.sh
- vector
- Java_com_example_objectdetection_MainActivity_initObjectDetection
- create_chapters.sh

## God Nodes (most connected - your core abstractions)
1. `ObjectDetector` - 41 edges
2. `ReviewsHandler` - 26 edges
3. `YOLO` - 16 edges
4. `MNISTDataset` - 16 edges
5. `Node` - 13 edges
6. `MLFlow` - 13 edges
7. `ModelImpl` - 11 edges
8. `FoldStats` - 10 edges
9. `YOLOResult` - 10 edges
10. `IsolationForest` - 10 edges

## Surprising Connections (you probably didn't know these)
- `Performance` --references--> `ParallelCrossValidate()`  [INFERRED]
  homlcpp/chapter003/dlib/README.md → homlcpp/chapter003/dlib/grid-dlib.cc
- `main()` --calls--> `GenerateData()`  [INFERRED]
  homlcpp/chapter010/dlib/mlp-dlib.cc → homlcpp/chapter010/data/data.cc
- `main()` --calls--> `GenerateData()`  [INFERRED]
  homlcpp/chapter010/flashlight/mlp_fl.cc → homlcpp/chapter010/data/data.cc
- `main()` --calls--> `ReadPapersReviews()`  [INFERRED]
  homlcpp/chapter002/hdf5/hdf5.cpp → homlcpp/chapter002/json/reviewsreader.cpp
- `main()` --calls--> `ReadPapersReviews()`  [INFERRED]
  homlcpp/chapter002/json/json.cc → homlcpp/chapter002/json/reviewsreader.cpp

## Import Cycles
- None detected.

## Communities (61 total, 30 thin omitted)

### Community 0 - "ReviewsHandler"
Cohesion: 0.05
Nodes (16): main(), main(), HandlerState, Global, None, Paper, PapersArray, Review (+8 more)

### Community 1 - "fl_classify.cc"
Cohesion: 0.11
Nodes (12): fill_values(), main(), read_row_help(), load_dataset(), main(), apply_classifier(), load_dataset(), main() (+4 more)

### Community 2 - "dlib-anomaly.cc"
Cohesion: 0.35
Nodes (7): CombineDatasets(), IsolationForest(), LoadDataset(), main(), MultivariateGaussianDist(), OneClassSvm(), PlotClusters()

### Community 3 - "grid_fl.cc"
Cohesion: 0.53
Nodes (3): generate_data(), main(), make_samples_polynomial()

### Community 4 - "local development environment"
Cohesion: 0.11
Nodes (16): arrayfire, build notes for newer packages, building and running the samples, cuda version on local, cudnn, dlib (CUDA + GUI support), flashlight, folder structure (+8 more)

### Community 5 - "mlpack-cluster.cc"
Cohesion: 0.07
Nodes (14): GenerateData(), main(), GenerateData(), main(), DoDBScanClustering(), DoGMMClustering(), DoKMeansClustering(), DoMeanShiftClustering() (+6 more)

### Community 7 - "install_env.sh"
Cohesion: 0.25
Nodes (4): checkout_lib.sh script, install_env.sh script, install_lib_custom.sh script, install_lib.sh script

### Community 8 - "string"
Cohesion: 0.05
Nodes (15): ImdbDataset, ImdbDataset::ImdbDataset(), reader_, tokenizer_, ImdbReader, ImdbReader::ImdbReader(), max_size_, neg_samples_ (+7 more)

### Community 9 - "env_scripts/README.md"
Cohesion: 0.33
Nodes (5): Building development environment, Building development environment with Docker, Building local development environment, Configure you GitHub account first, List of all third-party libraries

### Community 10 - "install_android.sh"
Cohesion: 0.40
Nodes (4): ANDROID_ABI, ANDROID_NDK, ANDROID_STL_SHARED, install_android.sh script

### Community 11 - "grid-dlib.cc"
Cohesion: 0.09
Nodes (18): FoldStats, n, sum_abs_err, sum_abs_err_sq, sum_sq_err, sum_x, sum_xx, sum_xy (+10 more)

### Community 12 - "dlib-cluster.cc"
Cohesion: 0.19
Nodes (11): DoGraphClustering(), DoGraphNewmanClustering(), DoHierarhicalClustering(), DoKMeansClustering(), DoSpectralClustering(), knn_kernel, edges_, samples_ (+3 more)

### Community 14 - "tapkee-dr.cc"
Cohesion: 0.20
Nodes (6): gaussian_kernel_callback, gamma, main(), Plot3DData(), PlotClusters(), Reduction()

### Community 15 - "ModelImpl"
Cohesion: 0.15
Nodes (5): ModelImpl, bert_, dropout_, fc1_, fc2_

### Community 18 - "filesystem"
Cohesion: 0.11
Nodes (9): GenerateData(), GenerateNoiseData(), main(), PlotResults(), ABClassification(), ConvertToCSV(), DTClassification(), main() (+1 more)

### Community 21 - "machine-learning-cpp — agent instructions"
Cohesion: 0.20
Nodes (9): ast-grep, Build, Code Style, Context Retrieval Policy, graphify, Layout, machine-learning-cpp — agent instructions, Response Style (+1 more)

### Community 26 - "chapter003 / flashlight"
Cohesion: 0.50
Nodes (3): Build, chapter003 / flashlight, Run

### Community 27 - "chapter003 / mlpack"
Cohesion: 0.50
Nodes (3): Build, chapter003 / mlpack, Run

### Community 31 - "dlib-save.cc"
Cohesion: 0.56
Nodes (6): func(), LoadAndPredictKRR(), LoadAndPredictNetwork(), main(), TrainAndSaveKRR(), TrainAndSaveNetwork()

### Community 32 - "YOLO"
Cohesion: 0.05
Nodes (22): DensityEstimationTree(), KernelDensityEstimation(), LoadDataset(), main(), MultivariateGaussianDist(), PlotClusters(), IOU(), mat2tensor() (+14 more)

### Community 35 - "eigen_recommender.cc"
Cohesion: 0.07
Nodes (14): read_data(), LoadMovies(), LoadRatings(), CalculateWeightedMse(), InitialiseMatrix(), main(), PrintRecommendations(), RatingsPredictions() (+6 more)

### Community 36 - "isolation-forest.h"
Cohesion: 0.10
Nodes (18): CalcC(), DatasetRange, dataset, indices, IsolationForest, c, rand_engine, trees (+10 more)

### Community 37 - "MNISTDataset"
Cohesion: 0.07
Nodes (14): LeNet5Impl, conv_, full_, main(), show_pytorch_version(), CvImageToTensor(), MNISTDataset, columns_ (+6 more)

### Community 38 - "ObjectDetector"
Cohesion: 0.07
Nodes (16): ObjectDetector, android_app_, camera_device_, camera_id_, camera_mgr_, capture_request_, capture_session_, height_ (+8 more)

### Community 39 - "mlpack-classify.cc"
Cohesion: 0.13
Nodes (10): LRClassification(), main(), PlotClasses(), SMRClassification(), SVMClassification(), KFoldDataSet, fold_size, k (+2 more)

### Community 41 - "MLFlow"
Cohesion: 0.14
Nodes (10): main(), make_dataset(), check_result(), handle_result(), log_param(), MLFlow, enabled_, experiment_id_ (+2 more)

### Community 44 - "detector.cpp"
Cohesion: 0.18
Nodes (5): onDisconnected(), onError(), onSessionActive(), onSessionClosed(), onSessionReady()

### Community 46 - "NetImpl"
Cohesion: 0.19
Nodes (6): func(), main(), NetImpl, l1_, l2_, l3_

### Community 47 - "dlib-dr.cc"
Cohesion: 0.17
Nodes (7): LDAReduction(), main(), PCACompression(), PCAReduction(), PlotClusters(), SammonReduction(), labels

### Community 51 - "download_sentiment_data.sh"
Cohesion: 0.67
Nodes (5): download(), download_archive(), download_huggingface(), download_sentiment_data.sh script, usage()

### Community 52 - "vector"
Cohesion: 0.07
Nodes (13): Paper, id, preliminary_decision, reviews, Review, confidence, evaluation, id (+5 more)

## Knowledge Gaps
- **94 isolated node(s):** `Global`, `None`, `Paper`, `PapersArray`, `Review` (+89 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 396 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **30 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `ObjectDetector` connect `ObjectDetector` to `YOLO`, `detector.cpp`, `native-lib.cpp`, `.process_image`?**
  _High betweenness centrality (0.067) - this node is a cross-community bridge._
- **What connects `Global`, `None`, `Paper` to the rest of the system?**
  _94 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `ReviewsHandler` be split into smaller, more focused modules?**
  _Cohesion score 0.05102040816326531 - nodes in this community are weakly interconnected._
- **Why does `YOLO` connect `YOLO` to `ObjectDetector`?**
  _High betweenness centrality (0.029) - this node is a cross-community bridge._
- **Should `fl_classify.cc` be split into smaller, more focused modules?**
  _Cohesion score 0.1053763440860215 - nodes in this community are weakly interconnected._
- **Should `local development environment` be split into smaller, more focused modules?**
  _Cohesion score 0.1111111111111111 - nodes in this community are weakly interconnected._
- **Should `mlpack-cluster.cc` be split into smaller, more focused modules?**
  _Cohesion score 0.0707070707070707 - nodes in this community are weakly interconnected._