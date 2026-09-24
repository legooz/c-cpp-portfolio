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
#include "../cpp/insertion-sort/insertion.cpp"
#undef main

int main() {

    std::mt19937 random(42);
    for (int n = 0; n <= 100; ++n) {
        std::vector<int> actual;
        for (int i = 0; i < n; ++i) actual.push_back(static_cast<int>(random() % 101) - 50);
        if (n > 1) { actual[0] = INT_MIN; actual[1] = INT_MAX; }
        auto expected = actual;
        std::sort(expected.begin(), expected.end());
        insertionSort(n, actual.data());
        CHECK(actual == expected);
    }

    return 0;
}
