#include <algorithm>
#include <array>
#include <climits>
#include <iostream>
#include <limits>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#define CHECK(condition) do { if (!(condition)) throw std::runtime_error("Check failed: " #condition); } while (false)
template<class Exception, class Function> void expectThrow(Function operation) {
    bool caught = false;
    try { operation(); } catch (const Exception&) { caught = true; }
    CHECK(caught);
}

#define main demo_main_0
#include "../cpp/maze-generation/main.cpp"
#undef main

int main() {
    static_assert(WIDTH == 40 && HEIGHT == 40);
    std::mt19937 random(7);
    Grid empty;
    for (auto& row : empty) row.fill(' ');
    auto base = empty;
    divide(base, 1, 1, 2, 20, random); // Width <= 2 terminates.
    CHECK(base == empty);
    divide(base, 1, 1, 20, 2, random); // Height <= 2 terminates.
    CHECK(base == empty);
    Grid horizontal;
    for (auto& row : horizontal) row.fill('X');
    for (int y = 1; y <= 3; ++y) for (int x = 1; x <= 3; ++x) horizontal[y][x] = ' ';
    horizontal[2][0] = horizontal[2][4] = ' ';
    divide(horizontal, 1, 1, 3, 3, random); // Square means horizontal; only row 2 is eligible.
    CHECK(horizontal[2][1] == ' ' && horizontal[2][3] == ' ');
    auto vertical = empty;
    divide(vertical, 1, 1, 4, 3, random); // Width > height means vertical.
    for (int x = 2; x <= 3; ++x)
        CHECK(vertical[1][x] == ' ' && vertical[3][x] == ' '); // Existing end passages survive.
    CHECK(generateMaze(42) == generateMaze(42));
    CHECK(generateMaze(42) != generateMaze(43));

    for (unsigned seed = 0; seed < 100; ++seed) {
        auto grid = generateMaze(seed);
        int open = 0;
        for (int y = 0; y < HEIGHT; ++y) for (int x = 0; x < WIDTH; ++x) {
            if (x == 0 || y == 0 || x == WIDTH-1 || y == HEIGHT-1) CHECK(grid[y][x] == 'X');
            if (grid[y][x] == ' ') ++open;
        }
        std::queue<std::pair<int,int>> pending; std::set<std::pair<int,int>> seen;
        pending.push({1,1}); seen.insert({1,1});
        while (!pending.empty()) {
            auto [x,y] = pending.front(); pending.pop();
            for (auto p : {std::pair<int,int>{x+1,y}, {x-1,y}, {x,y+1}, {x,y-1}})
                if (p.first > 0 && p.first < WIDTH-1 && p.second > 0 && p.second < HEIGHT-1 &&
                    grid[p.second][p.first] == ' ' && seen.insert(p).second) pending.push(p);
        }
        CHECK(static_cast<int>(seen.size()) == open);
        CHECK(open < (WIDTH-2)*(HEIGHT-2));
    }

    return 0;
}
