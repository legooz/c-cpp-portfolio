#include <array>
#include <iostream>
#include <random>
#include <string>

// An odd-sized lattice keeps walls on even coordinates and doors on odd ones.
constexpr int WIDTH = 41, HEIGHT = 41;
using Grid = std::array<std::string, HEIGHT>;

void divide(Grid& grid, int left, int top, int right, int bottom, std::mt19937& random) {
    if (right - left < 2 || bottom - top < 2) return;
    if (right - left > bottom - top) {
        std::uniform_int_distribution<int> wall_choice(0, (right - left) / 2 - 1);
        std::uniform_int_distribution<int> door_choice(0, (bottom - top) / 2);
        const int wall = left + 1 + 2 * wall_choice(random);
        const int door = top + 2 * door_choice(random);
        for (int y = top; y <= bottom; ++y) grid[y][wall] = (y == door ? ' ' : 'X');
        divide(grid, left, top, wall - 1, bottom, random);
        divide(grid, wall + 1, top, right, bottom, random);
    } else {
        std::uniform_int_distribution<int> wall_choice(0, (bottom - top) / 2 - 1);
        std::uniform_int_distribution<int> door_choice(0, (right - left) / 2);
        const int wall = top + 1 + 2 * wall_choice(random);
        const int door = left + 2 * door_choice(random);
        for (int x = left; x <= right; ++x) grid[wall][x] = (x == door ? ' ' : 'X');
        divide(grid, left, top, right, wall - 1, random);
        divide(grid, left, wall + 1, right, bottom, random);
    }
}
Grid generateMaze(unsigned seed) {
    Grid grid;
    for (int y = 0; y < HEIGHT; ++y) {
        grid[y] = std::string(WIDTH, ' ');
        for (int x = 0; x < WIDTH; ++x)
            if (!x || !y || x == WIDTH - 1 || y == HEIGHT - 1) grid[y][x] = 'X';
    }
    std::mt19937 random(seed);
    divide(grid, 1, 1, WIDTH - 2, HEIGHT - 2, random);
    return grid;
}
int main() {
    for (const auto& row : generateMaze(42)) std::cout << row << '\n';
    return 0;
}
