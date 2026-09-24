# C & C++ Portfolio

[![Build and test](https://github.com/legooz/c-cpp-portfolio/actions/workflows/ci.yml/badge.svg)](https://github.com/legooz/c-cpp-portfolio/actions/workflows/ci.yml)

**Lars Goozen · C11 · C++17 · Linux / WSL**

A collection of 27 small programs developed from 2023–2025 coursework and reviewed in September 2026. The examples cover resource-allocation safety, parallel reduction, POSIX processes and threads, recursive search, data structures, and input handling. Each program builds independently through one CMake project.

The 2026 review corrected algorithm and memory-safety defects, extracted C++ from eight notebooks, and added repeatable tests and CI. These are educational exercises, with course scaffolding where applicable. The review and test infrastructure were developed with AI assistance; this repository does not present the refreshed code as untouched historical submissions. See [the review record](docs/REVIEW.md) and [attribution](NOTICE.md).

## Start here

| Example | What to inspect | Evidence |
|---|---|---|
| [MPI minimum reduction](c/mpi-minimum/mpi-minimum.c) | Uneven `MPI_Scatterv` partitions, empty ranks, `INT_MAX` identity, separate serial reference | 20 MPI scenarios, including negative values, integer limits, non-divisible sizes, and more ranks than values |
| [Banker's safety algorithm](c/bankers/bankers_algorithm.c) | Resource invariants, safe sequences, validated input, wide accumulation | 60 generated states checked against exhaustive process-order search, plus invalid input and integer limits |
| [Maze search](cpp/maze-search/maze.hpp) and [class interface](cpp/maze-class/Maze.h) | Depth-first search, backtracking, owned state, bounded coordinates, full paths | Independent BFS reachability checks on 200 generated mazes and a 210-cell path regression |
| [ZIP barcode codec](cpp/zipcode-codec/zipcode.cpp) | Validated 2-of-5 encoding and decoding, repeatable calls, leading zeros | Exhaustive round trips for all 100,000 five-digit values and malformed barcode tests |
| [Playlist](cpp/playlist/PlaylistManagementSystem.cpp) | Linked-list reversal, append, shuffle, ownership and cleanup | Empty-list cases, exact ordering, permutation checks, and leak detection |

The smaller examples are indexed in [PROJECTS.md](docs/PROJECTS.md), including their executable names, inputs, assumptions, and regression coverage.

## Build and test

On Ubuntu / Ubuntu under WSL:

```sh
sudo apt-get update
sudo apt-get install -y build-essential cmake python3 libopenmpi-dev openmpi-bin
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build --parallel
ctest --test-dir build --output-on-failure
```

MPI is enabled by default. For the core examples without MPI, configure with `-DBUILD_MPI=OFF`. POSIX process and thread programs require a Unix-like system; the verified platform is Ubuntu Linux under WSL.

To include the optional OpenGL demo and its two-pixel rendering check:

```sh
sudo apt-get install -y freeglut3-dev xvfb
cmake -S . -B build -DBUILD_OPENGL=ON
cmake --build build --parallel
ctest --test-dir build --output-on-failure
```

For memory and undefined-behavior checks:

```sh
cmake -S . -B build-sanitize -DCMAKE_BUILD_TYPE=Debug -DENABLE_SANITIZERS=ON -DBUILD_OPENGL=ON
cmake --build build-sanitize --parallel
ctest --test-dir build-sanitize --output-on-failure
```

GCC/Clang builds treat `-Wall -Wextra -Wpedantic` warnings as errors. CI runs normal and AddressSanitizer/UndefinedBehaviorSanitizer configurations. Leak detection stays enabled for the core examples; it is disabled for the MPI and OpenGL test processes because those external runtimes manage process-lifetime allocations. Sanitizers are checks, not a proof that no defects remain.

## Try the programs

```sh
# Safe resource allocation: 20 claims, 20 allocations, 4 available counts.
./build/bankers < examples/bankers-safe.txt

# Uneven distribution across three MPI ranks; the minimum is -100.
mpirun -n 3 ./build/mpi_minimum --values 10 9 8 7 -100

# A generated workload with a reproducible seed.
mpirun -n 4 ./build/mpi_minimum 100003 42

./build/maze_search
./build/zipcode_codec
./build/playlist
./build/leading_digits examples/numbers.txt
./build/vowel_runs examples/words.txt
printf '0 4294967295\n' | ./build/hamming_distance
printf 'racecar n\n' | ./build/palindrome

# Fork, run a child command, wait, and propagate its exit status.
./build/process_info /bin/echo 'Hello from the child'
./build/threads_with_semaphore
```

Maze demos use seed 42 for repeatability. Random wall placement can legitimately produce an unsolvable maze; the solver reports that outcome. The separate recursive-division generator produces connected open cells. Neither solver promises a shortest path. The ZIP exercise uses a simplified format without a postal checksum; the word cipher is a classroom byte-manipulation exercise.

## Provenance

The release contains selected C/C++ source from a private coursework archive, with fresh Git history. It omits grades, student identifiers, assignment documents, notebook outputs, and unrelated coursework. [provenance.json](provenance.json) identifies the original source paths, notebook cell indices, and source-content hashes; [NOTICE.md](NOTICE.md) preserves attribution and explains licensing. The original archive remains separate.
