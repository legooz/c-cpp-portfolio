#include "Maze.h"
#include <iostream>

int main() {
    const Maze model;
    for (const auto& row : model.grid()) std::cout << row << '\n';
    const auto path = model.solve();
    if (path.empty()) std::cout << "No solution found.\n";
    else for (auto [x, y] : path) std::cout << x << ',' << y << '\n';
    return 0;
}
