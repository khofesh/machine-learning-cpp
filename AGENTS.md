# machine-learning-cpp — agent instructions

Personal workspace following *Hands-on Machine Learning with C++ (2nd ed.)*, plus *Learning Modern C++ for Finance*.

## Layout

- `homlcpp/chapterNNN/<topic>/<lib>/` — my own code per book chapter, one executable per library (eigen, blaze, xtensor, dlib, arrayfire, mlpack, flashlight, opencv, hdf5, ...)
- `homlcpp/chapter002/data/` — small sample datasets (iris, reviews.json)
- `check_torch/` — libtorch smoke test
- `Hands-on-Machine-learning-with-C-Second-Edition/`, `LearningModCppFinance/` — upstream book repos (git submodules, read-only reference; don't edit)
- `development/libs/` — manually built/installed third-party libs (libtorch, headers in `include/`); `development/*.sh`, `env_scripts/` — install scripts
- `build/`, `temp/`, `cudnn/` — ignored

## Build

- C++17, CMake >= 3.10, Fedora, GCC, CUDA 12.9
- Dependencies via vcpkg at `/home/fahmad/vcpkg` (toolchain included in root `CMakeLists.txt`); libtorch from `development/libs/libtorch`; ArrayFire in `/opt`
- Configure: `cmake -B build -S . -DCMAKE_BUILD_TYPE=Debug`
- Build: `cmake --build build --parallel`
- Build one target: `cmake --build build --target <name>`
- New example: add a subdirectory with its own `CMakeLists.txt` and register it with `add_subdirectory` in the parent
- Libraries in `development/libs/include` need `target_include_directories(<target> PRIVATE ${MANUAL_LIBS_INCLUDE_DIR})`
- Library install quirks (flashlight patch, cudnn, nccl, libtorch + CUDA 12.9) are documented in `README.md`

## Response Style

- Be extremely concise. No pleasantries, no filler.
- When asked to write code, return code only unless explanation is explicitly requested.
- No sycophantic preambles ("Sure!", "Great question!", "Absolutely!").
- No "Here's a function that..." preambles.
- Don't restate the question before answering.
- No "Note:", "Tip:", or "Remember:" appendices unless asked.
- No usage examples unless asked.
- No unsolicited suggestions or improvements beyond what was asked.
- Use short variable names where meaning is clear from context.

## Code Style

- Modern C++17; follow the style of the book examples in the same chapter
- One small self-contained `main` per example; keep each library's example independent of the others
- Prefer the library's native types (`Eigen::MatrixXf`, `af::array`, `arma::mat`, `torch::Tensor`, ...) over hand-rolled loops
- RAII, no raw `new`/`delete`; `const` and references for non-trivial parameters
- Data paths come from `argv` or are relative to the source dir — no absolute paths in code
- Minimal inline comments — only for non-obvious math or library quirks

## Context Retrieval Policy

Always retrieve the smallest amount of information necessary.
Escalate only when necessary. Stop escalating as soon as sufficient information has been obtained.

Preferred order:

1. Need code structure? graphify (`graphify-out/`, see the graphify section below).
2. Need symbols? `ast-grep`.
3. Need repository metadata? `rtk`.
4. Need implementation? Source files.
5. Use repository-wide search as last resort.

Avoid reading entire directories or the whole repository unless explicitly requested. Never scan `development/libs/` (tens of GB of third-party code) or `build/`.

## RTK (Rust Token Killer) - Token-Optimized CLI

`rtk` is a CLI proxy that filters and compresses command outputs, saving 60-90% tokens.

**Always** prefix commands with `rtk`. If RTK has a dedicated filter, it uses it. If not, it passes through unchanged.

```bash
rtk ls <path>
rtk read <file>
rtk find <pattern>
rtk git status
rtk git log -10
rtk err <cmd>           # Filter errors only from any command (e.g. rtk err cmake --build build)
rtk log <file>          # Deduplicated logs with counts
rtk json <file>         # JSON structure without values
```

## ast-grep

Prefer `ast-grep` over `grep` when searching C++ source (function/class/method definitions, includes, structural patterns), e.g. `ast-grep -l cpp -p 'Eigen::MatrixXf $X'`.

Use `grep` only for Markdown, JSON, YAML, CMake, logs and other plain text.

## graphify

This project has a knowledge graph at graphify-out/ with god nodes, community structure, and cross-file relationships.

Rules:
- For codebase questions, first run `graphify query "<question>"` when graphify-out/graph.json exists. Use `graphify path "<A>" "<B>"` for relationships and `graphify explain "<concept>"` for focused concepts. These return a scoped subgraph, usually much smaller than GRAPH_REPORT.md or raw grep output.
- If graphify-out/wiki/index.md exists, use it for broad navigation instead of raw source browsing.
- Read graphify-out/GRAPH_REPORT.md only for broad architecture review or when query/path/explain do not surface enough context.
- After modifying code, run `graphify update .` to keep the graph current (AST-only, no API cost).
