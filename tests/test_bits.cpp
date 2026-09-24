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
#include "../cpp/hamming-distance/goozen_lab14.cpp"
#undef main

int main() {

    CHECK(countBitsSetToOne(0) == 0); CHECK(countBitsSetToOne(UINT32_MAX) == 32);
    CHECK(countBitsSetToOne(1U << 31U) == 1);
    std::mt19937 random(9);
    for (int i = 0; i < 10000; ++i) {
        const auto n = static_cast<std::uint32_t>(random());
        CHECK(countBitsSetToOne(n) == std::bitset<32>(n).count());
    }

    return 0;
}
