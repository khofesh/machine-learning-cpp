# Graph Report - machine-learning-cpp  (2026-09-19)

## Corpus Check
- 39 files · ~86,388 words
- Verdict: corpus is large enough that graph structure adds value.

## Summary
- 154 nodes · 163 edges · 22 communities (11 shown, 3 thin omitted)
- Extraction: 99% EXTRACTED · 1% INFERRED · 0% AMBIGUOUS · INFERRED: 2 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `4292a7d5`
- Run `git rev-parse HEAD` and compare to check if the graph is stale.
- Run `graphify update .` after code changes (no API cost).

## Community Hubs (Navigation)
- ReviewsHandler
- csv.cpp
- GenerateData
- Review
- Hands-on machine learning with C++ 2nd edition
- CLAUDE.md
- install_env.sh
- ReadPapersReviews
- env_scripts/README.md
- install_android.sh
- GenerateData
- run_container.sh
- homlcpp/README.md
- machine-learning-cpp — agent instructions

## God Nodes (most connected - your core abstractions)
1. `ReviewsHandler` - 26 edges
2. `Review` - 12 edges
3. `machine-learning-cpp — agent instructions` - 9 edges
4. `Paper` - 9 edges
5. `Hands-on machine learning with C++ 2nd edition` - 6 edges
6. `local development environment` - 6 edges
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

## Communities (22 total, 3 thin omitted)

### Community 0 - "ReviewsHandler"
Cohesion: 0.08
Nodes (17): binary_t, exception, HandlerState, string, ReviewsHandler, error_, paper_, papers_ (+9 more)

### Community 1 - "csv.cpp"
Cohesion: 0.20
Nodes (12): vector, fill_values(), main(), read_row_help(), string, load_dataset(), main(), index_sequence (+4 more)

### Community 2 - "GenerateData"
Cohesion: 0.18
Nodes (7): pair, Vector, GenerateData(), main(), func(), main(), Matrix

### Community 3 - "Review"
Cohesion: 0.10
Nodes (16): string, vector, Paper, id, preliminary_decision, reviews, string, Review (+8 more)

### Community 4 - "Hands-on machine learning with C++ 2nd edition"
Cohesion: 0.17
Nodes (11): arrayfire, cuda version on local, flashlight, folder structure, Hands-on machine learning with C++ 2nd edition, local development environment, nccl, pytorch (+3 more)

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

## Knowledge Gaps
- **49 isolated node(s):** `Layout`, `Build`, `Response Style`, `Code Style`, `Context Retrieval Policy` (+44 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 93 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **3 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `ReviewsHandler` connect `ReviewsHandler` to `ReadPapersReviews`, `Review`?**
  _High betweenness centrality (0.194) - this node is a cross-community bridge._
- **Why does `Paper` connect `Review` to `ReviewsHandler`?**
  _High betweenness centrality (0.190) - this node is a cross-community bridge._
- **What connects `Layout`, `Build`, `Response Style` to the rest of the system?**
  _49 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `ReviewsHandler` be split into smaller, more focused modules?**
  _Cohesion score 0.08045977011494253 - nodes in this community are weakly interconnected._
- **Should `Review` be split into smaller, more focused modules?**
  _Cohesion score 0.09881422924901186 - nodes in this community are weakly interconnected._