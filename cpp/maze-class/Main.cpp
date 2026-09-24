#include "Maze.h"
#include <iostream>
#include "../common/random_seed.h"

int main(int argc, char** argv) {
    try {
        const Maze model(seedFromArguments(argc, argv));
        for (const auto& row : model.grid()) std::cout << row << '\n';
        const auto path = model.solve();
        if (path.empty()) std::cout << "No solution found.\n";
        else for (auto [x, y] : path) std::cout << x << ',' << y << '\n';
    } catch (const std::exception& error) {
        std::cerr << error.what() << "\nUsage: maze_class [seed]\n";
        return 1;
    }
    return 0;
}
