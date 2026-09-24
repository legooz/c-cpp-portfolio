# Validation record

Reviewed on September 24, 2026, on Ubuntu 24.04 under WSL.

| Configuration | Result |
|---|---|
| GCC/G++ 13.3.0, C11/C++17, Debug, `-Wall -Wextra -Wpedantic -Werror` | All 27 programs and 19 C++ test executables built successfully |
| Normal build, MPI and OpenGL enabled | 22/22 CTest groups passed |
| AddressSanitizer + UndefinedBehaviorSanitizer build, MPI and OpenGL enabled | 22/22 CTest groups passed; no reported sanitizer defects |

Other tools: CMake 3.28.3, Python 3.12.3, Open MPI 4.1.6, GLUT/Mesa with Xvfb. The [GitHub Actions workflow](https://github.com/legooz/c-cpp-portfolio/actions/workflows/ci.yml) repeats both build configurations on Ubuntu.

Coverage includes:

- All 100,000 five-digit ZIP-code round trips, frame and digit validation, and repeated calls.
- Banker's algorithm compared against exhaustive permutations for 60 generated states, including checking each reported safe sequence.
- Twenty MPI launches with exact independent expected results or required rejection, including 1, 2, 3, 4, 5, 8 and 11 ranks.
- Two hundred random-wall mazes checked against a BFS reachability oracle, a 210-cell path regression, and 100 recursive-division mazes checked for connected open cells.
- Randomized sorting/sortedness tests, integer-boundary arithmetic, FIFO and priority-queue behavior, list cleanup, and playlist permutations.
- Ten repeated runs each of synchronized and unsynchronized thread output; child exit, signal and exec-failure handling.
- File errors, malformed numeric input, long palindrome strings, first-word handling, and two OpenGL framebuffer pixel checks.

Leak detection remains enabled for core programs. MPI and OpenGL test processes set `ASAN_OPTIONS=detect_leaks=0` to exclude external runtime allocation lifetimes; address/undefined-behavior instrumentation remains active in those programs. Thread-sanitizer and OS-resource fault injection were not run. The graphics test samples two pixels, not a complete interactive session. Tests do not prove absence of all defects or compliance with unavailable assignment rubrics.
