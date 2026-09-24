#include "maze.hpp"
#include <iostream>
#include "../common/random_seed.h"

int main(int argc, char** argv) {
    try {
        const auto [grid, start] = maze::generate(seedFromArguments(argc, argv));
        const auto path = maze::solve(grid, start);
        for (const auto& row : grid) std::cout << row << '\n';
        std::cout << "Start: " << start.first << ',' << start.second << '\n';
        if (path.empty()) std::cout << "No solution found.\n";
        else {
            std::cout << "Path (start through exit):\n";
            for (auto [x, y] : path) std::cout << x << ',' << y << '\n';
        }
    } catch (const std::exception& error) {
        std::cerr << error.what() << "\nUsage: maze_search [seed]\n";
        return 1;
    }
    return 0;
}
