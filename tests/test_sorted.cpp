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
#include "../cpp/recursive-sorted/lab06.cpp"
#undef main

int main() {

    CHECK(isSorted(nullptr, 0));
    int values[] = {INT_MIN, -1, -1, 0, INT_MAX};
    CHECK(isSorted(values, 5));
    std::mt19937 random(7);
    for (int n = 1; n <= 100; ++n) {
        std::vector<int> data;
        for (int i = 0; i < n; ++i) data.push_back(static_cast<int>(random() % 8));
        CHECK(isSorted(data.data(), n) == std::is_sorted(data.begin(), data.end()));
    }

    return 0;
}
