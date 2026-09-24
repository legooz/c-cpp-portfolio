#include <type_traits>
#include <algorithm>
#include <array>
#include <climits>
#include <iostream>
#include <limits>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#define CHECK(condition) do { if (!(condition)) throw std::runtime_error("Check failed: " #condition); } while (false)
template<class Exception, class Function> void expectThrow(Function operation) {
    bool caught = false;
    try { operation(); } catch (const Exception&) { caught = true; }
    CHECK(caught);
}

#define main demo_main_0
#include "../cpp/vowel-runs/Source.cpp"
#undef main

int main() {
    static_assert(std::is_same_v<decltype(&consecVowels), int (*)(const char*)>);
    char word[word_capacity];
    std::istringstream input("abstemious zombies");
    CHECK(readWord(input, word) && std::strcmp(word, "abstemious") == 0);
    CHECK(readWord(input, word) && std::strcmp(word, "zombies") == 0);
    CHECK(!readWord(input, word));
    std::istringstream oversized("abcdefghijklmn");
    expectThrow<std::length_error>([&] { readWord(oversized, word); });

    CHECK(consecVowels("") == 0); CHECK(consecVowels("rhythm") == 0);
    CHECK(consecVowels("AEIOU") == 5); CHECK(consecVowels("queueing") == 5);
    CHECK(consecVowels("aeXio") == 2); CHECK(!vowelCheck(static_cast<char>(0xff)));

    return 0;
}
