#pragma once
#include <algorithm>
#include <array>
#include <random>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace maze {
constexpr int width = 20, height = 20;
using Grid = std::array<std::string, height>;
using Point = std::pair<int, int>; // (x, y)
using Path = std::vector<Point>;

inline bool inside(Point p) {
    return p.first >= 0 && p.first < width && p.second >= 0 && p.second < height;
}
inline bool search(const Grid& grid, std::array<std::array<bool, width>, height>& seen,
                   Point current, Path& path) {
    if (!inside(current)) return false;
    const auto [x, y] = current;
    if (seen[y][x] || grid[y][x] == 'X') return false;
    seen[y][x] = true;
    path.push_back(current);
    if (grid[y][x] == 'E') return true;
    for (auto next : {Point{x, y - 1}, Point{x, y + 1}, Point{x - 1, y}, Point{x + 1, y}})
        if (search(grid, seen, next, path)) return true;
    path.pop_back();
    return false;
}
inline Path solve(const Grid& grid, Point start) {
    for (const auto& row : grid)
        if (row.size() != width) throw std::invalid_argument("Maze row must have 20 cells");
    std::array<std::array<bool, width>, height> seen{};
    Path path;
    search(grid, seen, start, path);
    return path;
}
inline std::pair<Grid, Point> generate(unsigned seed) {
    Grid grid;
    std::vector<Point> cells;
    for (int y = 0; y < height; ++y) {
        grid[y] = std::string(width, 'X');
        for (int x = 1; y > 0 && y < height - 1 && x < width - 1; ++x) {
            grid[y][x] = ' ';
            cells.emplace_back(x, y);
        }
    }
    std::mt19937 random(seed);
    std::shuffle(cells.begin(), cells.end(), random);
    const std::size_t walls = cells.size() / 4;
    for (std::size_t i = 0; i < walls; ++i) grid[cells[i].second][cells[i].first] = 'X';
    const auto exit = cells[walls];
    grid[exit.second][exit.first] = 'E';
    return {grid, cells[walls + 1]};
}
}
