#include "maze.hpp"
#include <iostream>

int main() {
    const auto [grid, start] = maze::generate(42);
    const auto path = maze::solve(grid, start);
    for (const auto& row : grid) std::cout << row << '\n';
    std::cout << "Start: " << start.first << ',' << start.second << '\n';
    if (path.empty()) std::cout << "No solution found.\n";
    else {
        std::cout << "Path (start through exit):\n";
        for (auto [x, y] : path) std::cout << x << ',' << y << '\n';
    }
    return 0;
}
