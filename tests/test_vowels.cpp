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

    CHECK(consecVowels("") == 0); CHECK(consecVowels("rhythm") == 0);
    CHECK(consecVowels("AEIOU") == 5); CHECK(consecVowels("queueing") == 5);
    CHECK(consecVowels("aeXio") == 2); CHECK(!vowelCheck(static_cast<char>(0xff)));

    return 0;
}
