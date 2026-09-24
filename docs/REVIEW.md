# September 2026 correctness review

## Scope

The source archive was at commit `c17ca3e7f63e3b792aea60a16504732b916488c0`. The review found 14 standalone C++ programs, five C programs, and eight additional C++ programs embedded in data-structures notebooks: **27 executable examples**. The remaining notebooks are outside this C/C++ review.

The final saved `%%writefile` cell was used where a notebook wrote a filename more than once. Source was extracted as text; notebook package-install and shell cells were not executed. Earlier variants remain in the private archive. The publication has fresh history, so private archive contents and historical metadata are not imported into this repository.

The goal is executable, documented learning examples. Original assignment rubrics were not available in the source archive, so this review checks the contracts documented here and in the program index; it does not certify historical grading compliance. The changes were developed with AI assistance and include substantive rewrites where the original structure was unsafe or incorrect.

## Findings and repairs

| Area | Archived behavior | Published repair and evidence |
|---|---|---|
| MPI reduction | Partition size was hard-coded to `arraySize / 8`; other process counts could omit values or access beyond the array. Minima started at 999999. Rank 0's full-array minimum masked partition errors in the final reduction. | Uses actual communicator size and `MPI_Scatterv` counts/displacements including remainders. Local reductions start at `INT_MAX`; the serial reference is separate. Explicit-array tests put the minimum in the remainder and use values above the old sentinel, negative extremes, one value, and 11 ranks. |
| Banker's algorithm | The safety loop was broadly correct for valid resources, but unchecked `scanf_s`, negative resources, allocation above claim, and signed resource accumulation could invalidate results. | Portable bounded token parsing, resource invariants, wide work-vector accumulation, and explicit safe sequences. Sixty generated cases are checked against all possible process orders, with independent verification of the returned sequence. |
| POSIX processes | A fixed `pstree` command and 100-second sleeps obscured failures; the parent did not reap its child. | Configurable child command, checked `fork`/`exec`, `_exit(127)` on failed exec, EINTR-aware `waitpid`, exit/signal propagation, flushed output and no sleeps. Tests check matching IDs and several termination modes. |
| POSIX threads | Thread routines fell off a non-void function; creation, joining and semaphore calls were unchecked. | Defined returns, semaphore EINTR handling, partial-creation cleanup, checked joins and output failures. Synchronized output is intact; unsynchronized output preserves characters without assuming a schedule. |
| ZIP codec | Greedy encoding failed to set the second bar for digits 1, 2, 4 and 7. Reused objects accumulated output. Barcode shape and digits were unchecked. | Validated lookup codes, independent results for each call, leading zeros and strict frame/length/digit checks. Every value from 00000 to 99999 round-trips. |
| First maze solver | Exit placement could loop forever after an occupied first pick, repeatedly creating exits. Wall attempts were counted even on duplicates, path buffers were too small, printing stopped after 100 entries, and exit coordinates were omitted. | A shuffled cell selection gives exactly 81 interior walls and distinct start/exit cells. DFS uses a vector with backtracking and includes the exit. Independent BFS agrees on reachability for 200 seeds; a 210-cell snake verifies long paths. |
| Maze class | Constructor-local dimensions did not initialize state; start could equal exit; the saved path omitted the exit. Low-level public array helpers were easy to misuse. | Owns initialized grid/start state, validates construction, and uses the corrected solver with fresh visited state on each call. Tests compare its path with the free-function interface. |
| Recursive maze generation | Heap-allocated coordinate scalars leaked on early returns; hard-coded coordinate 2 could escape a recursive subregion. | Reworked recursive division with local scalar values and an odd 41x41 lattice. Even walls and odd doors preserve connectivity. Border and whole-grid reachability checks cover 100 seeds. |
| Leading-digit histogram | `% 10` selected the last digit, fixed-size reads fabricated zeros for short/missing files, and zero was counted under one. | Streams validated integer tokens of any length; determines the first nonzero digit, skips zero values and reports input errors. Tests distinguish first/last digits and exercise signs and leading zeros. |
| Palindrome | Unbounded extraction into a 15-byte allocation could overwrite memory; input failure was not handled. | Uses `std::string`/`std::string_view`, checked extraction, and case-sensitive comparison. Tests include 10,000-character CLI input and a 100,000-character function input. |
| Word cipher | Cast a `char` buffer to `int*`, relying on alignment, aliasing, endianness and signed arithmetic. | Explicit little-endian `uint32_t` loading/subtraction/decoding, with escaped non-printable output. Key 491 recovers the expected plaintext; unsigned wraparound is tested. |
| Linked lists and playlist | Remaining nodes were leaked; a default node's integer was uninitialized. | Initialized values, destructors/cleanup, and deleted copying for owning lists. Mutation, reversal, shuffle preservation and sanitizer leak checks cover the retained behavior. |
| Queue | Empty operations returned uninitialized scalar values. | Empty operations throw `std::out_of_range`; FIFO, clearing, reuse and copies are tested. |
| Recursive algorithms | Selection sort and sorted-check base cases did not handle empty inputs. | Empty-range termination plus randomized reference comparisons. Recursive functions remain bounded educational examples. |
| Tree examples | Main duplicated a template implementation rather than exercising the supplied source. The final traversal cell performed post-order under the name `preOrder`. | Uses the supplied node implementation with initialized values and parent-link updates; provides all three correctly named traversals. Node links remain non-owning. |
| Priority queue | Comparator used name length despite stored numeric priorities. The original rubric was not retained. | Defines larger numeric priority as the portfolio contract; tests conflicting name lengths, negative priorities and ties. This is a documented behavior choice, not a claim about the missing rubric. |
| Pair operators | Operators were implemented only in the demo entry-point file; signed addition could overflow. | Operators link from the class implementation, getters are const, and addition throws on overflow. Tests cover each operand order and integer boundaries. |
| Movie sorting | Constructor assigned local variables instead of members; sort length was fixed at six. | Initializes members, accepts a checked length, and keeps ratings paired with titles. Duplicate, empty and malformed-length cases are tested. |
| Vowel scanning | An initial read discarded the first word; missing/empty files produced misleading output. | Processes every word, handles case consistently, reports file failures and uses documented first-wins tie handling. |
| Hamming distance | Failed extraction could leave uninitialized operands; integer width was implicit. | Validated `uint32_t` inputs and exact 32-bit output; 10,000 population counts are checked against `std::bitset`. |
| OpenGL | Small drawing demo depended on instructor-provided framework; only compilation had been checked previously. | Retains framework credit and adds a two-pixel Xvfb/Mesa check for the blue background and yellow triangle. No broader graphics or performance claim. |

The MPI distribution follows the count/displacement semantics documented by [Open MPI](https://www.open-mpi.org/doc/v4.0/man3/MPI_Scatterv.3.php).

## Validation

The repository defines 22 CTest groups when MPI and OpenGL are enabled: 19 C++ unit executables, one CLI regression suite (eight unittest cases), one MPI suite (20 launches), and one graphics check. CLI tests also run every non-MPI/non-OpenGL demonstration, exercise malformed input, and repeat thread tests ten times.

Validation was performed on Ubuntu 24.04 under WSL with GCC/G++ 13.3.0, CMake 3.28.3, Python 3.12.3, and Open MPI 4.1.6. The exact publication validation results are recorded in [VALIDATION.md](VALIDATION.md).

Tests are independent oracles where practical (`std::sort`, `std::is_sorted`, `std::bitset`, BFS, exhaustive Banker permutations, and Python integer minima). They do not establish formal correctness for all executions. Fault injection for exhausted OS resources, other operating systems, and broad graphics-device coverage are outside the tested scope.
