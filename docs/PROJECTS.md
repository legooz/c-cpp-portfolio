# Program index

All paths below are relative to the repository root. Executables appear in the CMake build directory. C programs use C11; C++ programs use C++17.

## C programs (5)

| Executable | Source | Behavior and tests |
|---|---|---|
| `bankers` | [c/bankers](../c/bankers) | Fixed 5-process, 4-resource safety check. Read claim matrix, allocation matrix, available vector from stdin: exactly 44 integers in 0..INT_MAX. Optional `--request PROCESS(1..5) R1 R2 R3 R4` checks and tentatively allocates a request; denial preserves the state. Safe/unsafe and granted/denied are valid results (exit 0); malformed resources exit 1. Safe-sequence validity is checked against an exhaustive oracle. Unsafe means no guaranteed completion order under maximum claims, not proof of a currently deadlocked system. |
| `process_info` | [process_info.c](../c/posix/process_info.c) | POSIX `fork`, `execvp`, `waitpid`. With no arguments runs `pstree -p` rooted at the parent PID (requires `psmisc`); otherwise runs the supplied command. Tests match parent/child IDs and successful, failed, missing, and signal-terminated commands. |
| `threads_with_semaphore` | [thread source](../c/posix/thread_output_with_semaphore.c) | 20 threads, one semaphore protecting each complete message. Tests require exactly 20 intact messages. |
| `threads_without_semaphore` | [thread source](../c/posix/thread_output_without_semaphore.c) | Same workload without a message-level semaphore. POSIX stdio protects each character call; whole messages can interleave. Tests check character conservation, not a particular schedule. |
| `mpi_minimum` | [c/mpi-minimum](../c/mpi-minimum) | No arguments or `--assignment [seed]` requires eight ranks and broadcasts 8,000,000 generated values in 0..1,000,000,000. Extension modes: `size [seed]` or `--values INT...`, using `MPI_Scatterv` with any positive rank count. Size 1..10,000,000; integers and seed must fit `int`. Distributes all elements, reduces local minima, and checks a separately computed serial result. Empty overall inputs are rejected; empty rank partitions are supported. No benchmark claim. |

## C++ programs (23)

| Executable | Source | Behavior and tests |
|---|---|---|
| `maze_search` | [maze-search](../cpp/maze-search) | Recursive DFS through a 20x20 grid with `X` walls and `E` exit. A vector retains the complete path including its exit. Bounds, unreachable exits, long paths and BFS reachability are tested. |
| `maze_class` | [maze-class](../cpp/maze-class) | Encapsulates grid/start state and reuses the corrected solver. Repeated solving does not retain visited state. Constructors validate dimensions and coordinates. |
| `maze_generation` | [maze-generation](../cpp/maze-generation) | Recursive division on a 41x41 odd lattice. BFS checks that every open cell is connected across 100 seeds. Heap-allocated scalar coordinates were removed. |
| `zipcode_codec` | [zipcode-codec](../cpp/zipcode-codec) | Frame bars plus five 2-of-5 digits, without a checksum. Stores one integer, returns integer ZIP/string barcode, and keeps helpers private. Encodes leading zeros for 00000..99999; repeated calls and malformed-input exceptions are tested. All values round-trip. |
| `playlist` | [playlist](../cpp/playlist) | Linked-list front/end insertion, reversal, shuffle and output. The list owns its nodes and disallows copying. Tests cover empty lists, order, and preservation of every song. Recovered from notebook cell 3. |
| `linked_list_operations` | [linked-list-operations](../cpp/linked-list-operations) | Owns integer nodes; insert/find/delete-first/delete-second. Empty and single-node lists are safe; copying is disabled. Destruction frees remaining nodes. |
| `linked_list_basics` | [linked-list-basics](../cpp/linked-list-basics) | Two manually linked nodes, initialized values and explicit cleanup. Exact output and leak checks. |
| `queues` | [queues](../cpp/queues) | FIFO wrapper around `std::list`. Empty `front`/`dequeue` throw `std::out_of_range`. Tests cover FIFO order, clearing, reuse and independent copies. |
| `priority_queues` | [priority-queues](../cpp/priority-queues) | `std::priority_queue<Person>` serves larger numeric priorities first. Equal-priority order is unspecified. The archived comparator used name length; numeric priority matches the recovered reference notebook; no separate grading rubric was found. |
| `binary_trees` | [binary-trees](../cpp/binary-trees) | Non-owning templated node links, parent tracking, in-order traversal. Caller owns nodes and must provide an acyclic, consistently linked tree. Defaults, replacement links and traversal are tested. |
| `tree_traversal` | [tree-traversal](../cpp/tree-traversal) | Pre-order, in-order and post-order traversals of a caller-owned tree, tested with null and asymmetric inputs. |
| `selection_sort` | [selection-sort](../cpp/selection-sort) | Recursive selection sort with inclusive indices; empty ranges terminate. Random arrays compared with `std::sort`, including duplicates and integer extremes. O(n²) time, O(n) recursion. |
| `insertion_sort` | [insertion-sort](../cpp/insertion-sort) | In-place insertion sort. Same reference tests. O(n²) worst-case time, O(1) extra storage. |
| `recursive_sorted` | [recursive-sorted](../cpp/recursive-sorted) | Recursive nondecreasing-order check, with empty/singleton base cases. Compared with `std::is_sorted`. O(n) time and recursion. |
| `command_product` | [command_product.cpp](../cpp/recursive-sorted/command_product.cpp) | Lab 6 part 2, added in 2026. Multiplies any number of signed 64-bit CLI integers, subject to OS argument limits. Validates input and rejects results outside signed 64-bit range; zero and sign-boundary cases are tested. |
| `pair_operators` | [pair-operators](../cpp/pair-operators) | Pair+pair, pair+integer and integer+pair. Operators link from the class implementation, preserve operands and throw on signed overflow. |
| `movie_sort` | [movie-sort](../cpp/movie-sort) | Selection sort by case-sensitive title. Name and rating stay together. Tests cover defaults, duplicates and empty input; caller supplies a valid array and its length. |
| `leading_digits` | [leading-digits](../cpp/leading-digits) | Reads whitespace-separated signed decimal integer tokens from a filename (default `enrollments.txt`). Counts first nonzero digits, excluding all-zero values. Handles arbitrarily long integer tokens without numeric conversion. |
| `vowel_runs` | [vowel-runs](../cpp/vowel-runs) | Uses C-strings in 14-byte arrays, as required by Lab 5. Reads words of at most 13 characters from a filename (default `bigwords.txt`); longer tokens are rejected safely. Finds the longest consecutive ASCII vowel run, case-insensitively. First word wins ties. Reports empty/missing files. |
| `palindrome` | [palindrome](../cpp/palindrome) | Reads a word, then optional `y` to repeat. Case-sensitive byte comparison. `std::string` replaces an overflowing fixed buffer; empty, even/odd-length, and long inputs are tested. |
| `hamming_distance` | [hamming-distance](../cpp/hamming-distance) | Reads two unsigned 32-bit decimal integers; XOR plus population count. Rejects malformed/out-of-range inputs. Tested against `std::bitset` on 10,000 values. |
| `word_cipher` | [word-cipher](../cpp/word-cipher) | Subtracts trial keys 0..500 from four explicitly little-endian unsigned words. Key 491 gives `Attack at dawn!!`. Non-printable output is escaped; no aliasing or alignment-dependent casts. |
| `opengl_shapes` | [opengl-shapes](../cpp/opengl-shapes) | Optional GLUT window with blue background/yellow triangle. `--smoke-test` checks two framebuffer pixels under Xvfb. Framework credit is retained. This is a rendering smoke test, not comprehensive graphics QA. |

## Testing boundaries

Recovered requirements and remaining gaps are documented in [ASSIGNMENT_AUDIT.md](ASSIGNMENT_AUDIT.md). The tests check selected functional properties and regressions, plus sanitizer-detectable memory errors during those runs. Thread failure paths are reviewed but OS resource-exhaustion failures are not fault-injected. Graphics checks sample two pixels. Deep recursive algorithms are intended for bounded learning examples, not unbounded inputs. Linux/WSL is the tested platform; other OS/compiler combinations have not been verified.
