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
#include "../cpp/maze-class/Maze.cpp"
#undef main

int main() {

    maze::Grid blocked; for (auto& row : blocked) row = std::string(maze::width, 'X');
    CHECK(maze::solve(blocked, {1, 1}).empty());
    CHECK(maze::solve(blocked, {-1, 0}).empty());
    blocked[1][1] = 'E';
    CHECK(maze::solve(blocked, {1, 1}) == maze::Path({{1, 1}}));
    expectThrow<std::invalid_argument>([&] { Maze invalid(blocked, {-1, 1}); });
    maze::Grid malformed = blocked; malformed[0] = "";
    expectThrow<std::invalid_argument>([&] { maze::solve(malformed, {0, 0}); });
    // A one-cell snake exceeds the old 200-coordinate buffer and 100-step output.
    maze::Grid snake; for (auto& row : snake) row = std::string(maze::width, 'X');
    for (int y = 0; y < maze::height; y += 2) {
        snake[y] = std::string(maze::width, ' ');
        if (y + 1 < maze::height) snake[y+1][(y / 2) % 2 == 0 ? maze::width-1 : 0] = ' ';
    }
    snake[19][0] = 'E';
    CHECK(maze::solve(snake, {0, 0}).size() == 210);
    for (unsigned seed = 0; seed < 200; ++seed) {
        auto [grid, start] = maze::generate(seed);
        int walls = 0, exits = 0;
        for (int y = 1; y < maze::height-1; ++y)
            for (int x = 1; x < maze::width-1; ++x) {
                walls += grid[y][x] == 'X'; exits += grid[y][x] == 'E';
            }
        CHECK(walls == 81 && exits == 1 && grid[start.second][start.first] == ' ');
        auto path = maze::solve(grid, start);
        // Independent BFS oracle checks whether an exit is reachable.
        std::queue<maze::Point> pending; std::set<maze::Point> seen;
        pending.push(start); seen.insert(start); bool reachable = false;
        while (!pending.empty()) {
            auto [x,y] = pending.front(); pending.pop();
            if (grid[y][x] == 'E') reachable = true;
            for (auto p : {maze::Point{x+1,y}, {x-1,y}, {x,y+1}, {x,y-1}})
                if (maze::inside(p) && grid[p.second][p.first] != 'X' && seen.insert(p).second) pending.push(p);
        }
        CHECK(!path.empty() == reachable);
        CHECK(Maze(grid, start).solve() == path);
        if (path.empty()) continue;
        CHECK(path.front() == start); CHECK(grid[path.back().second][path.back().first] == 'E');
        std::set<maze::Point> unique;
        for (std::size_t i = 0; i < path.size(); ++i) {
            CHECK(unique.insert(path[i]).second);
            CHECK(grid[path[i].second][path[i].first] != 'X');
            if (i) CHECK(std::abs(path[i].first-path[i-1].first) + std::abs(path[i].second-path[i-1].second) == 1);
        }
    }

    return 0;
}
