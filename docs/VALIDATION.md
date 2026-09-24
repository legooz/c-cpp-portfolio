# Validation record

Reviewed on September 24, 2026, on Ubuntu 24.04 under WSL.

| Configuration | Result |
|---|---|
| GCC/G++ 13.3.0, C11/C++17, Debug, `-Wall -Wextra -Wpedantic -Werror` | All 29 programs, 21 C++ test executables and one C test executable built successfully |
| Normal build, MPI and OpenGL enabled | 25/25 CTest groups passed |
| AddressSanitizer + UndefinedBehaviorSanitizer build, MPI and OpenGL enabled | 25/25 CTest groups passed; no reported sanitizer defects |

Other tools: CMake 3.28.3, Python 3.12.3, Open MPI 4.1.6, GLUT/Mesa with Xvfb. The [GitHub Actions workflow](https://github.com/legooz/c-cpp-portfolio/actions/workflows/ci.yml) repeats both build configurations on Ubuntu.

Coverage includes:

- All 100,000 five-digit ZIP-code round trips, frame and digit validation, and repeated calls.
- Banker's algorithm compared against exhaustive permutations for 60 generated states, including checking each reported safe sequence. Request tests also cover grants, unavailable resources, exceeded claims, unsafe tentative allocations and unchanged state after denial.
- Twenty-four MPI launches, including two complete eight-million-element assignment broadcasts, with exact independent expected results or required rejection, including 1, 2, 3, 4, 5, 8 and 11 ranks.
- Two hundred random-wall mazes checked against a BFS reachability oracle, a 210-cell path regression, and 100 40x40 recursive-division mazes checked for connected open cells, plus preservation of existing wall-end passages.
- Randomized sorting/sortedness tests, integer-boundary arithmetic and pointer increments, FIFO and priority-queue behavior, list cleanup, and playlist permutations.
- Ten repeated runs each of synchronized and unsynchronized thread output; required parent/child process-tree display plus child exit, signal and exec-failure handling.
- File errors, malformed numeric input, palindrome pointer traversal, exact 14-character input limits and oversized-input rejection, C-string capacity boundaries, command-line product overflow/sign/zero cases, and four OpenGL framebuffer pixel checks.
- Both original datasets independently checked: 3,295 enrollments and 87,314 words; exact results are recorded in [ASSIGNMENT_AUDIT.md](ASSIGNMENT_AUDIT.md).
- The complete OpenGL framebuffer was captured and visually inspected after correcting the square: [rendered example](images/opengl-shapes.png). The cipher's pointer conversions also passed an optimized `-O2` build with signed-boundary regressions.

Leak detection remains enabled for core programs. MPI and OpenGL test processes set `ASAN_OPTIONS=detect_leaks=0` to exclude external runtime allocation lifetimes; address/undefined-behavior instrumentation remains active in those programs. Thread-sanitizer and OS-resource fault injection were not run. The graphics test samples four pixels, not a complete interactive session. Recovered instruction and reference-notebook coverage are listed in [ASSIGNMENT_AUDIT.md](ASSIGNMENT_AUDIT.md); tests do not establish compliance with unavailable requirements or prove absence of all defects.
