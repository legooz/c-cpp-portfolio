#include "../common/random_seed.h"
#include <array>
#include <iostream>
#include <random>

constexpr int WIDTH = 40, HEIGHT = 40;
using Grid = std::array<std::array<char, WIDTH>, HEIGHT>;

// Inclusive bounds describe the open region, excluding its surrounding walls.
void divide(Grid& grid, int left, int top, int right, int bottom, std::mt19937& random) {
    const int width = right - left + 1, height = bottom - top + 1;
    if (width <= 2 || height <= 2) return;
    if (height >= width) {
        const int wall = std::uniform_int_distribution<int>(top + 1, bottom - 1)(random);
        for (int x = left; x <= right; ++x) grid[wall][x] = 'X';
        // Preserve passages through earlier walls at both ends of the new wall.
        if (grid[wall][left - 1] == ' ') grid[wall][left] = ' ';
        if (grid[wall][right + 1] == ' ') grid[wall][right] = ' ';
        grid[wall][std::uniform_int_distribution<int>(left, right)(random)] = ' ';
        divide(grid, left, top, right, wall - 1, random);
        divide(grid, left, wall + 1, right, bottom, random);
    } else {
        const int wall = std::uniform_int_distribution<int>(left + 1, right - 1)(random);
        for (int y = top; y <= bottom; ++y) grid[y][wall] = 'X';
        if (grid[top - 1][wall] == ' ') grid[top][wall] = ' ';
        if (grid[bottom + 1][wall] == ' ') grid[bottom][wall] = ' ';
        grid[std::uniform_int_distribution<int>(top, bottom)(random)][wall] = ' ';
        divide(grid, left, top, wall - 1, bottom, random);
        divide(grid, wall + 1, top, right, bottom, random);
    }
}
Grid generateMaze(unsigned seed) {
    Grid grid;
    for (int y = 0; y < HEIGHT; ++y)
        for (int x = 0; x < WIDTH; ++x)
            grid[y][x] = (!x || !y || x == WIDTH - 1 || y == HEIGHT - 1) ? 'X' : ' ';
    std::mt19937 random(seed);
    divide(grid, 1, 1, WIDTH - 2, HEIGHT - 2, random);
    return grid;
}
int main(int argc, char** argv) {
    try {
        for (const auto& row : generateMaze(seedFromArguments(argc, argv))) {
            for (char cell : row) std::cout << cell;
            std::cout << '\n';
        }
    } catch (const std::exception& error) {
        std::cerr << error.what() << "\nUsage: maze_generation [seed]\n";
        return 1;
    }
    return 0;
}
