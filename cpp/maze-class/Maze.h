#pragma once
#include "../maze-search/maze.hpp"

class Maze {
public:
    Maze();
    explicit Maze(unsigned seed);
    Maze(maze::Grid grid, maze::Point start);
    void generateMaze();
    void generateMaze(unsigned seed);
    maze::Path solve() const;
    const maze::Grid& grid() const { return grid_; }
    maze::Point start() const { return start_; }
private:
    maze::Grid grid_{};
    maze::Point start_{};
};
