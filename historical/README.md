# Historical C and C++ exercises

Seventeen additional programs recovered from CSCE A201 (Fall 2021 and Fall 2022) and CSCE A211 (Spring 2023) coursework at the University of Alaska Anchorage. These are original learning exercises. They complement the reviewed programs elsewhere in this repository; their implementation logic has been preserved, including defects described below.

| Folder | Contents |
| --- | --- |
| [C fundamentals, 2021](c-fundamentals) | Eight exercises in decimal/binary conversion, arrays, string comparison/search and arithmetic |
| [Binary range](c-experiments/binary-range) | A binary table for small integers |
| [Temperature conversion](c-experiments/temperature-conversion) | Fahrenheit/Celsius arithmetic |
| [Temperature equality](c-experiments/temperature-equality) | Search for the equal Fahrenheit/Celsius value |
| [Monty Hall](c-experiments/monty-hall) | Random simulation of switching and staying |
| [Math library](c-experiments/math-library) | Header/source separation, absolute value and Babylonian square root |
| [Coin change](cpp-fundamentals/coin-change) | Reference parameters and denomination counts |
| [Josephus problem](cpp-fundamentals/josephus) | Circular linked-list elimination |
| [Checked array](cpp-fundamentals/checked-array) | Templates and bounds exceptions |
| [Linked-list lab](cpp-fundamentals/linked-list-editor) | Adding, finding, editing and removing string nodes |

Course scaffolding and collaborator credits remain; repeated sole-author banners are centralized on the shared portfolio attribution page. Original joint-author and copyright notices remain in `integer_math.c`; the shared attribution page identifies the contributors. A student identifier was removed from `decimal_string_addition.c`. See the repository [NOTICE](../NOTICE.md) and the `historical_recovery` section of [provenance.json](../provenance.json).

## Build and sample checks

These programs are separate from the root CMake targets. Each folder has its own `main`, and the 2021 files are separate programs. Linux/WSL GCC and G++ can compile them with:

```sh
gcc -std=c11 -Wall -Wextra c-fundamentals/decimal_to_binary.c -o /tmp/to-binary
gcc -std=c11 -Wall -Wextra c-experiments/math-library/*.c -o /tmp/math-library
g++ -std=c++14 -Wall -Wextra cpp-fundamentals/checked-array/main.cpp -o /tmp/checked-array
g++ -std=c++17 -Wall -Wextra cpp-fundamentals/josephus/*.cpp -o /tmp/josephus
```

The checked-array exercise uses dynamic exception specifications, which require C++14 or earlier. Other C++ examples use C++17. [VALIDATION.json](VALIDATION.json) records compile and sample checks, including compiler warnings. Successful compilation and sample runs do not establish general correctness.

## Known historical limitations

- The 2021 basic-math exercise reverses subtraction operands. Its string helpers also have edge-case defects, including reverse character search skipping index zero. Decimal string arithmetic and substring matching should be treated as unreviewed learning code.
- The binary-to-decimal exercise first accumulates the bit string as decimal digits in an `int`; long inputs can overflow. Input routines generally assume valid, bounded input.
- Babylonian square root assumes a positive value, and the integer absolute-value function does not handle the most-negative `int`.
- The Josephus program does not free every removed node and does not safely handle all small or invalid inputs. Use the sample only as historical pointer practice.
- The linked-list lab assumes a nonempty list for `addTail`; non-head removal leaks a node. The checked array has no safe copy semantics.
- The random simulation is an educational experiment, not a statistical validation.

Unfinished drafts, duplicated versions, instructor-only examples and build artifacts are kept outside the public collection. No logic fixes were made in this recovery pass. The [engineering portfolio](https://github.com/legooz/engineering-portfolio) connects this category with the other recovered work.
