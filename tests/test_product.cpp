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


#define main product_demo_main
#include "../cpp/recursive-sorted/command_product.cpp"
#undef main
int main() {
    CHECK(checkedProduct({-2, -3}) == 6);
    CHECK(checkedProduct({0, LLONG_MIN}) == 0);
    CHECK(checkedProduct({LLONG_MIN, 1}) == LLONG_MIN);
    CHECK(checkedProduct({LLONG_MAX, 1}) == LLONG_MAX);
    CHECK(checkedProduct({LLONG_MIN / 2, 2}) == LLONG_MIN);
    CHECK(checkedProduct({LLONG_MIN, -1, -1}) == LLONG_MIN);
    CHECK(checkedProduct({LLONG_MIN / 2, -2, -1}) == LLONG_MIN);
    CHECK(checkedProduct({LLONG_MAX, LLONG_MAX, 0}) == 0);
    expectThrow<std::overflow_error>([] { checkedProduct({LLONG_MIN, -1}); });
    expectThrow<std::overflow_error>([] { checkedProduct({-1, LLONG_MIN}); });
    expectThrow<std::overflow_error>([] { checkedProduct({LLONG_MAX, 2}); });
    expectThrow<std::overflow_error>([] { checkedProduct({LLONG_MIN, 2}); });
    expectThrow<std::overflow_error>([] { checkedProduct({2, LLONG_MIN}); });
    return 0;
}
