# Graph Report - machine-learning-cpp  (2026-11-10)

## Corpus Check
- 49 files · ~90,315 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 16 file(s) not represented in the graph (top: .csv 7, (none) 6, .cmake 2)

## Summary
- 251 nodes · 299 edges · 35 communities (14 shown, 21 thin omitted)
- Extraction: 99% EXTRACTED · 1% INFERRED · 0% AMBIGUOUS · INFERRED: 3 edges (avg confidence: 0.88)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `e91dd4cb`
- Run `git rev-parse HEAD` and compare to check if the graph is stale.
- Run `graphify update .` after code changes (no API cost).

## Community Hubs (Navigation)
- ReviewsHandler
- knn_kernel
- GenerateData
- Review
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
- GenerateData
- objective
- chapter003 / flashlight
- chapter003 / mlpack
- linreg_dlib.cpp
- load_dataset
- GenerateData

## God Nodes (most connected - your core abstractions)
1. `ReviewsHandler` - 26 edges
2. `Review` - 12 edges
3. `FoldStats` - 10 edges
4. `Paper` - 9 edges
5. `machine-learning-cpp — agent instructions` - 9 edges
6. `local development environment` - 9 edges
7. `PlotClusters()` - 8 edges
8. `knn_kernel` - 8 edges
9. `ParallelCrossValidate()` - 7 edges
10. `PlotClusters()` - 7 edges

## Surprising Connections (you probably didn't know these)
- `Performance` --references--> `ParallelCrossValidate()`  [INFERRED]
  homlcpp/chapter003/dlib/README.md → homlcpp/chapter003/dlib/grid-dlib.cc
- `main()` --calls--> `ReadPapersReviews()`  [INFERRED]
  homlcpp/chapter002/hdf5/hdf5.cpp → homlcpp/chapter002/json/reviewsreader.cpp
- `main()` --calls--> `ReadPapersReviews()`  [INFERRED]
  homlcpp/chapter002/json/json.cc → homlcpp/chapter002/json/reviewsreader.cpp
- `ReviewsHandler` --references--> `Paper`  [EXTRACTED]
  homlcpp/chapter002/json/reviewsreader.cpp → homlcpp/chapter002/json/paper.h
- `ReviewsHandler` --references--> `Review`  [EXTRACTED]
  homlcpp/chapter002/json/reviewsreader.cpp → homlcpp/chapter002/json/review.h

## Import Cycles
- None detected.

## Communities (35 total, 21 thin omitted)

### Community 0 - "ReviewsHandler"
Cohesion: 0.07
Nodes (9): main(), main(), ReadPapersReviews(), ReviewsHandler, error_, paper_, papers_, review_ (+1 more)

### Community 1 - "knn_kernel"
Cohesion: 0.18
Nodes (6): fill_values(), main(), read_row_help(), knn_kernel, edges_, samples_

### Community 3 - "Review"
Cohesion: 0.09
Nodes (13): Paper, id, preliminary_decision, reviews, Review, confidence, evaluation, id (+5 more)

### Community 4 - "local development environment"
Cohesion: 0.14
Nodes (13): arrayfire, build notes for newer packages, cuda version on local, dlib (CUDA + GUI support), flashlight, flashlight (CUDA 13), folder structure, Hands-on machine learning with C++ 2nd edition (+5 more)

### Community 5 - "mlpack-cluster.cc"
Cohesion: 0.23
Nodes (6): DoDBScanClustering(), DoGMMClustering(), DoKMeansClustering(), DoMeanShiftClustering(), main(), PlotClusters()

### Community 7 - "install_env.sh"
Cohesion: 0.25
Nodes (4): checkout_lib.sh script, install_env.sh script, install_lib_custom.sh script, install_lib.sh script

### Community 8 - "dlib-cluster.cc"
Cohesion: 0.35
Nodes (7): DoGraphClustering(), DoGraphNewmanClustering(), DoHierarhicalClustering(), DoKMeansClustering(), DoSpectralClustering(), main(), PlotClusters()

### Community 9 - "env_scripts/README.md"
Cohesion: 0.33
Nodes (5): Building development environment, Building development environment with Docker, Building local development environment, Configure you GitHub account first, List of all third-party libraries

### Community 10 - "install_android.sh"
Cohesion: 0.40
Nodes (4): ANDROID_ABI, ANDROID_NDK, ANDROID_STL_SHARED, install_android.sh script

### Community 11 - "grid-dlib.cc"
Cohesion: 0.08
Nodes (18): FoldStats, n, sum_abs_err, sum_abs_err_sq, sum_sq_err, sum_x, sum_xx, sum_xy (+10 more)

### Community 21 - "machine-learning-cpp — agent instructions"
Cohesion: 0.20
Nodes (9): ast-grep, Build, Code Style, Context Retrieval Policy, graphify, Layout, machine-learning-cpp — agent instructions, Response Style (+1 more)

### Community 23 - "generate_data"
Cohesion: 0.53
Nodes (3): generate_data(), main(), make_samples_polynomial()

### Community 26 - "chapter003 / flashlight"
Cohesion: 0.50
Nodes (3): Build, chapter003 / flashlight, Run

### Community 27 - "chapter003 / mlpack"
Cohesion: 0.50
Nodes (3): Build, chapter003 / mlpack, Run

## Knowledge Gaps
- **30 isolated node(s):** `n`, `sum_sq_err`, `sum_abs_err`, `sum_abs_err_sq`, `sum_xy` (+25 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 144 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **21 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `knn_kernel` connect `knn_kernel` to `dlib-cluster.cc`?**
  _High betweenness centrality (0.210) - this node is a cross-community bridge._
- **What connects `n`, `sum_sq_err`, `sum_abs_err` to the rest of the system?**
  _30 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `ReviewsHandler` be split into smaller, more focused modules?**
  _Cohesion score 0.07057057057057058 - nodes in this community are weakly interconnected._
- **Why does `Paper` connect `Review` to `ReviewsHandler`?**
  _High betweenness centrality (0.193) - this node is a cross-community bridge._
- **Should `Review` be split into smaller, more focused modules?**
  _Cohesion score 0.09 - nodes in this community are weakly interconnected._
- **Why does `ReviewsHandler` connect `ReviewsHandler` to `Review`?**
  _High betweenness centrality (0.136) - this node is a cross-community bridge._
- **Should `local development environment` be split into smaller, more focused modules?**
  _Cohesion score 0.14285714285714285 - nodes in this community are weakly interconnected._