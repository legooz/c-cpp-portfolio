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
#include "../cpp/tree-traversal/mainTest.cpp"
#undef main

int main() {

    Node<int> root(2), left(1), right(3); root.setLeft(&left); root.setRight(&right);
    std::ostringstream output;
    auto* original = std::cout.rdbuf(output.rdbuf());
    preOrder(&root); output << '|'; inOrder(&root); output << '|'; postOrder(&root);
    preOrder<int>(nullptr); inOrder<int>(nullptr); postOrder<int>(nullptr);
    std::cout.rdbuf(original);
    CHECK(output.str() == "2 1 3 |1 2 3 |1 3 2 ");

    return 0;
}
