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
#include "../cpp/binary-trees/main.cpp"
#undef main

int main() {

    Node<int> root(2), left(1), right(3), replacement(0), empty;
    CHECK(empty.getItem() == 0 && empty.getLeft() == nullptr);
    root.setLeft(&left); root.setRight(&right);
    CHECK(left.getParent() == &root && right.getParent() == &root);
    std::ostringstream output;
    auto* original = std::cout.rdbuf(output.rdbuf());
    printInOrder(&root); printInOrder<int>(nullptr);
    std::cout.rdbuf(original);
    CHECK(output.str() == "1 2 3 ");
    root.setLeft(&replacement);
    CHECK(left.getParent() == nullptr && replacement.getParent() == &root);

    return 0;
}
