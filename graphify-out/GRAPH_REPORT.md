# Graph Report - machine-learning-cpp  (2026-09-20)

## Corpus Check
- 47 files · ~88,393 words
- Verdict: corpus is large enough that graph structure adds value.

## Summary
- 192 nodes · 202 edges · 30 communities (17 shown, 4 thin omitted)
- Extraction: 99% EXTRACTED · 1% INFERRED · 0% AMBIGUOUS · INFERRED: 2 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `66cad043`
- Run `git rev-parse HEAD` and compare to check if the graph is stale.
- Run `graphify update .` after code changes (no API cost).

## Community Hubs (Navigation)
- ReviewsHandler
- csv.cpp
- GenerateData
- Review
- local development environment
- chapter003 / dlib
- CLAUDE.md
- install_env.sh
- ReadPapersReviews
- env_scripts/README.md
- install_android.sh
- GenerateData
- run_container.sh
- homlcpp/README.md
- machine-learning-cpp — agent instructions
- generate_data
- GenerateData
- objective
- chapter003 / flashlight
- chapter003 / mlpack
- grid-dlib.cc

## God Nodes (most connected - your core abstractions)
1. `ReviewsHandler` - 26 edges
2. `Review` - 12 edges
3. `local development environment` - 9 edges
4. `Paper` - 9 edges
5. `machine-learning-cpp — agent instructions` - 9 edges
6. `Hands-on machine learning with C++ 2nd edition` - 5 edges
7. `fill_values()` - 5 edges
8. `read_row_help()` - 5 edges
9. `load_dataset()` - 5 edges
10. `GenerateData()` - 5 edges

## Surprising Connections (you probably didn't know these)
- `main()` --calls--> `ReadPapersReviews()`  [INFERRED]
  homlcpp/chapter002/hdf5/hdf5.cpp → homlcpp/chapter002/json/reviewsreader.cpp
- `main()` --calls--> `ReadPapersReviews()`  [INFERRED]
  homlcpp/chapter002/json/json.cc → homlcpp/chapter002/json/reviewsreader.cpp
- `ReviewsHandler` --references--> `Paper`  [EXTRACTED]
  homlcpp/chapter002/json/reviewsreader.cpp → homlcpp/chapter002/json/paper.h
- `ReviewsHandler` --references--> `Review`  [EXTRACTED]
  homlcpp/chapter002/json/reviewsreader.cpp → homlcpp/chapter002/json/review.h
- `Paper` --references--> `Review`  [EXTRACTED]
  homlcpp/chapter002/json/paper.h → homlcpp/chapter002/json/review.h

## Import Cycles
- None detected.

## Communities (30 total, 4 thin omitted)

### Community 0 - "ReviewsHandler"
Cohesion: 0.08
Nodes (17): binary_t, exception, HandlerState, string, ReviewsHandler, error_, paper_, papers_ (+9 more)

### Community 1 - "csv.cpp"
Cohesion: 0.20
Nodes (12): vector, fill_values(), main(), read_row_help(), string, Tensor, load_dataset(), main() (+4 more)

### Community 2 - "GenerateData"
Cohesion: 0.18
Nodes (7): pair, Vector, GenerateData(), main(), func(), main(), Matrix

### Community 3 - "Review"
Cohesion: 0.10
Nodes (16): string, vector, Paper, id, preliminary_decision, reviews, string, Review (+8 more)

### Community 4 - "local development environment"
Cohesion: 0.14
Nodes (13): arrayfire, build notes for newer packages, cuda version on local, dlib (CUDA + GUI support), flashlight, flashlight (CUDA 13), folder structure, Hands-on machine learning with C++ 2nd edition (+5 more)

### Community 5 - "chapter003 / dlib"
Cohesion: 0.50
Nodes (3): Build, chapter003 / dlib, Run

### Community 7 - "install_env.sh"
Cohesion: 0.25
Nodes (4): checkout_lib.sh script, install_env.sh script, install_lib_custom.sh script, install_lib.sh script

### Community 8 - "ReadPapersReviews"
Cohesion: 0.43
Nodes (3): main(), main(), ReadPapersReviews()

### Community 9 - "env_scripts/README.md"
Cohesion: 0.33
Nodes (5): Building development environment, Building development environment with Docker, Building local development environment, Configure you GitHub account first, List of all third-party libraries

### Community 10 - "install_android.sh"
Cohesion: 0.40
Nodes (4): ANDROID_ABI, ANDROID_NDK, ANDROID_STL_SHARED, install_android.sh script

### Community 11 - "GenerateData"
Cohesion: 0.50
Nodes (4): pair, GenerateData(), main(), MatrixXf

### Community 21 - "machine-learning-cpp — agent instructions"
Cohesion: 0.20
Nodes (9): ast-grep, Build, Code Style, Context Retrieval Policy, graphify, Layout, machine-learning-cpp — agent instructions, Response Style (+1 more)

### Community 23 - "generate_data"
Cohesion: 0.53
Nodes (5): pair, Tensor, generate_data(), main(), make_samples_polynomial()

### Community 24 - "GenerateData"
Cohesion: 0.40
Nodes (5): pair, GenerateData(), main(), mat, rowvec

### Community 26 - "chapter003 / flashlight"
Cohesion: 0.50
Nodes (3): Build, chapter003 / flashlight, Run

### Community 27 - "chapter003 / mlpack"
Cohesion: 0.50
Nodes (3): Build, chapter003 / mlpack, Run

### Community 28 - "grid-dlib.cc"
Cohesion: 0.43
Nodes (6): pair, GenerateData(), LinSpace(), main(), Labels, Samples

## Knowledge Gaps
- **57 isolated node(s):** `cuda version on local`, `flashlight`, `flashlight (CUDA 13)`, `nccl`, `pytorch` (+52 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 114 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **4 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `Paper` connect `Review` to `ReviewsHandler`?**
  _High betweenness centrality (0.146) - this node is a cross-community bridge._
- **Why does `ReviewsHandler` connect `ReviewsHandler` to `ReadPapersReviews`, `Review`?**
  _High betweenness centrality (0.136) - this node is a cross-community bridge._
- **Why does `Review` connect `Review` to `ReviewsHandler`?**
  _High betweenness centrality (0.048) - this node is a cross-community bridge._
- **What connects `cuda version on local`, `flashlight`, `flashlight (CUDA 13)` to the rest of the system?**
  _57 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `ReviewsHandler` be split into smaller, more focused modules?**
  _Cohesion score 0.08045977011494253 - nodes in this community are weakly interconnected._
- **Should `Review` be split into smaller, more focused modules?**
  _Cohesion score 0.09881422924901186 - nodes in this community are weakly interconnected._
- **Should `local development environment` be split into smaller, more focused modules?**
  _Cohesion score 0.14285714285714285 - nodes in this community are weakly interconnected._