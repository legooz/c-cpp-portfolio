# Assignment requirements audit

Reviewed September 24, 2026. Original instructions were recovered from local coursework files after the initial code review. They were absent from the Git archive. This audit compares the published implementations with those recovered instructions, including required interfaces and techniques as well as output.

Of the **27 archived executable examples**, 15 have direct assignment/tutorial instructions, seven have reference notebooks without a separate grading rubric, and five still have missing handouts. Lab 6 also requires a second executable absent from the archived project; the new `command_product` brings the portfolio to **28 programs**. It is a 2026 addition, not a recovered historical submission.

The requirements below are paraphrases. [assignment-evidence.json](assignment-evidence.json) records document basenames and SHA-256 hashes, without distributing the handouts or local paths. Evidence IDs in the tables refer to that file. Changes and tests were developed with AI assistance.

## Projects with recovered instructions

| Program / evidence | Required behavior or technique | Finding and published result |
|---|---|---|
| `pair_operators` — E00, Assignment 3 problem 1 | Separate headers/implementation; non-member friend addition in all operand orders; explain why an integer cannot be the left operand of a Pair member operator. | Operators already worked after the first review. Added the required explanation in `Pair.h`; three friend overloads preserve operands and check overflow. [Tests](../tests/test_pair.cpp). |
| `zipcode_codec` — E00, problem 2 | Integer and barcode constructors; exactly one stored representation; integer ZIP getter, string barcode getter; private helpers. Five two-of-five groups enclosed by frame bits. | The archived encoding was wrong for several digits and retained mutable output. The first refresh fixed encoding but exposed helpers and returned a string ZIP. The final class stores one integer, has the specified getter types, and makes helpers private. The handout's 99504 example and all 100,000 values round-trip. This exercise deliberately has no checksum. [Tests](../tests/test_zipcode.cpp). |
| `movie_sort` — E00, problem 3 | Movie class with constructors/getters/setters; an array containing the six specified titles/ratings; output sorted by name. | Retains the six required movies and fixes uninitialized constructor members and fixed-length sorting. Titles stay paired with ratings. [Tests](../tests/test_movie.cpp) and [CLI checks](../tests/test_cli.py). |
| `leading_digits` — E00, problem 4; E41, Assignment 1 | Count leading digits 1–9 in 3,295 enrollment values. Assignment 3 replaces Assignment 1's stdin redirection with an opened input file, and requires separate header/implementation files. | The archive counted trailing digits and mishandled short files and zeros. Corrected counting was confirmed against the original data, and a header/implementation split was added. The Assignment 3 input method takes precedence. [Tests](../tests/test_digits.cpp). |
| `maze_class` — E00, problem 5 | Refactor the Assignment 2 maze solution into a class with suitable constructors and methods; separate header/implementation. | The class now owns valid grid/start state and generates, solves and exposes results through methods. Constructor and full-path defects were fixed. The class requirements are met; the referenced Assignment 2 handout and attached solution were not recovered, so inherited assignment-specific behavior remains unverified. [Tests](../tests/test_maze.cpp). |
| `selection_sort` — E10, Lab 4 | Recursive selection sort, a swap function and a working demonstration. | Recursive sorting is retained; empty-range termination was repaired. Generated inputs agree with `std::sort`. [Tests](../tests/test_selection_sort.cpp). |
| `vowel_runs` — E11, Lab 5 | Use C-strings, not STL strings; words are at most 13 characters; read `bigwords.txt`, implement character-vowel and C-string run functions, and report the winning word. | The archive and first refresh used `std::string`, which violated the technique requirement. Now uses bounded 14-byte character arrays including the terminator. Also fixes skipping the first word and handles oversized/missing/empty input. [Tests](../tests/test_vowels.cpp). |
| `recursive_sorted` and new `command_product` — E12, Lab 6 | Part 1: recursive `isSorted(arr, n)`, no global variables. Part 2: a separate program multiplying an arbitrary number of integer command-line arguments. | Part 1 now handles empty/singleton ranges. Part 2 was absent from the archived project and has been added; `2 4 6` prints `48`. It accepts any argument count allowed by the OS, validates signed 64-bit inputs, handles zero, and rejects a result outside that range. [Sorted tests](../tests/test_sorted.cpp), [product tests](../tests/test_product.cpp), [CLI tests](../tests/test_cli.py). |
| `hamming_distance` — E01, Lab 14 | Read unsigned codewords, show differing bits, count their Hamming distance. | Keeps the XOR/differing-bit approach and validates 32-bit unsigned input. Ten thousand comparisons agree with `std::bitset`. [Tests](../tests/test_bits.cpp). |
| `mpi_minimum` — E03, architecture Assignment 3 problem 1 | Eight processes; rank 0 generates 8,000,000 integers in 0–1,000,000,000; broadcast the complete array; each rank searches its eighth; root obtains the minimum and independently scans the full array to verify it. | The archive's minimum sentinel and validation masked partition defects. The first refresh used generalized scattering, which did not match the required broadcast. No arguments or `--assignment [seed]` now runs the exact required workload using `MPI_Bcast` and `MPI_Reduce`, followed by a separate serial scan. Explicit size/value modes retain the generalized extension. Two full assignment runs plus 22 other MPI scenarios pass. [Tests](../tests/test_mpi.py). |
| `process_info` — E06, OS Tutorial 4 exercise | A forked child uses `execvp` to display a process tree with parent/child PIDs. | The archive invoked `pstree` but slept and did not reap the child. The first refresh defaulted to `true`, omitting the required display. The default now executes `pstree -p` rooted at the parent PID, and the parent waits and checks status. Optional commands remain an extension. [CLI tests](../tests/test_cli.py). |
| `threads_without_semaphore`, `threads_with_semaphore` — E40, OS Tutorial 7 exercise | Demonstrate character output from 20 pthreads, then synchronize it using an unnamed semaphore. | Both variants retain the required workload. Fixed thread returns and error handling; semaphore protection covers each whole message. Tests conserve all characters and require 20 intact synchronized messages without assuming thread order. [CLI tests](../tests/test_cli.py). |
| `bankers` — E08, OS Tutorial 8 | Implement the described Banker algorithm, including safety and resource-request phases. C/C++ and CLI are allowed; unspecified details may be assumed. | The archived safety-only implementation and first refresh lacked the request phase covered by the tutorial. Added claim/availability checks, tentative allocation, safety validation and commit only when safe. Every denial preserves the state. Fixed five-process/four-resource dimensions remain a documented assumption. [Request tests](../tests/test_bankers.c), [exhaustive safety oracle](../tests/test_cli.py). |
| `playlist` — E18, Homework 2 part 1 | Implement append, reverse and shuffle in the supplied linked-list playlist. | Those operations were already functionally implemented. The review repaired ownership/leaks and verified empty lists, reversal order and shuffle preservation. The notebook's separate prose FIFO/LIFO question is outside the executable audit. [Tests](../tests/test_playlist.cpp). |

## Original data verification

Both normal and sanitizer builds were run against the original input files and compared with independent Python calculations:

- `enrollments.txt`: 3,295 values. Counts for leading digits 1 through 9 are **1295, 789, 314, 230, 152, 118, 129, 164, 104**. SHA-256: `0f188f57529233cd651c1d970e11216748cbd0a2e977857b361cfe2bb68aef4e`.
- `bigwords.txt`: 87,314 words, maximum length 13. The first word with the longest vowel run is **cooeeing**, with five consecutive vowels. SHA-256: `e7ee7428b83ff0f49657c7d6fcd846c964c7cb2deb8db212e388b48bdf095629`.

The original datasets remain private; the public tests use small independent fixtures.

## Reference notebooks and missing handouts

The seven examples below were checked against their recovered notebook code and the regression tests, but the notebooks do not establish a separate grading rubric:

| Program | Evidence | Result |
|---|---|---|
| `binary_trees` | E13 | Default values, parent links and traversal tested; links remain non-owning. |
| `insertion_sort` | E26 | Matches the reference insertion-sort behavior and `std::sort`. |
| `linked_list_basics` | E27 | Required node linking/output retained; nodes are freed. |
| `linked_list_operations` | E28 | Insert/find/delete behavior retained; ownership and edge cases repaired. |
| `priority_queues` | E31 | The reference comparator uses numeric priority; the saved completed variant used name length. Published numeric-priority behavior matches the reference. A separate instruction asking for a name-length variation was not found. |
| `queues` | E35 | FIFO behavior retained; empty operations now throw instead of returning uninitialized data. |
| `tree_traversal` | E37 | Pre-, in- and post-order behavior tested; a mislabeled archived traversal was corrected. |

**Programming II Assignment 2 and Labs 7 and 9 were not found.** This leaves `maze_search`, `maze_generation`, `word_cipher`, `palindrome` and `opengl_shapes` without their original prompts. Their documented behavior is tested, but assignment compliance cannot be confirmed. Assignment 2 also limits the inherited-behavior assessment of `maze_class` described above.

This record verifies recovered programming requirements and tested behavior. It does not reconstruct historical grades or claim that the modern portfolio was the original submission. Build and memory-check results are in [VALIDATION.md](VALIDATION.md).
