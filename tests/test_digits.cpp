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
#include "../cpp/leading-digits/Source.cpp"
#undef main

int main() {

    CHECK(leadingDigit("1239") == 1); CHECK(leadingDigit("-9871") == 9);
    CHECK(leadingDigit("+00021") == 2); CHECK(leadingDigit("-000") == 0);
    CHECK(leadingDigit(std::string(100, '8')) == 8);
    for (const std::string bad : {"", "+", "-", "12a", "1.2", "1e2"})
        expectThrow<std::invalid_argument>([&] { leadingDigit(bad); });

    return 0;
}
