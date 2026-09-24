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
#include "../cpp/pair-operators/Pair.cpp"
#undef main

int main() {

    Pair a(5, 10), b(1, 2);
    auto sum = a + b;
    CHECK(sum.get1() == 6 && sum.get2() == 12);
    CHECK((2 + sum).get1() == 8 && (sum + 2).get2() == 14);
    CHECK(a.get1() == 5 && b.get2() == 2);
    CHECK(Pair().get1() == 0);
    CHECK((Pair(-3, 3) + Pair(3, -3)).get2() == 0);
    expectThrow<std::overflow_error>([] { (void)(Pair(INT_MAX, 0) + 1); });
    expectThrow<std::overflow_error>([] { (void)(-1 + Pair(0, INT_MIN)); });

    return 0;
}
