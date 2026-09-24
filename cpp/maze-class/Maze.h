#pragma once
#include "../maze-search/maze.hpp"

class Maze {
public:
    explicit Maze(unsigned seed = 42);
    Maze(maze::Grid grid, maze::Point start);
    void generateMaze(unsigned seed = 42);
    maze::Path solve() const;
    const maze::Grid& grid() const { return grid_; }
    maze::Point start() const { return start_; }
private:
    maze::Grid grid_{};
    maze::Point start_{};
};
