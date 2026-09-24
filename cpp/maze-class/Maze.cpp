#include "Maze.h"
#include <utility>

Maze::Maze(unsigned seed) { generateMaze(seed); }
Maze::Maze(maze::Grid grid, maze::Point start) : grid_(std::move(grid)), start_(start) {
    for (const auto& row : grid_)
        if (row.size() != maze::width) throw std::invalid_argument("Maze row must have 20 cells");
    if (!maze::inside(start_)) throw std::invalid_argument("Start is outside the maze");
}
void Maze::generateMaze(unsigned seed) {
    auto generated = maze::generate(seed);
    grid_ = std::move(generated.first);
    start_ = generated.second;
}
maze::Path Maze::solve() const { return maze::solve(grid_, start_); }
