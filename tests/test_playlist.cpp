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
#include "../cpp/playlist/PlaylistManagementSystem.cpp"
#undef main

int main() {

    Playlist list;
    list.reversePlaylist(); list.shufflePlaylist();
    list.addSongToEnd("A", "one"); list.addSongToEnd("B", "two"); list.addSong("C", "three");
    auto snapshot = [&] {
        std::ostringstream output;
        auto* original = std::cout.rdbuf(output.rdbuf());
        list.printPlaylist();
        std::cout.rdbuf(original);
        return output.str();
    };
    CHECK(snapshot() == "Playlist:\nC by three\nA by one\nB by two\n");
    list.reversePlaylist();
    CHECK(snapshot() == "Playlist:\nB by two\nA by one\nC by three\n");
    for (int i = 0; i < 100; ++i) {
        list.shufflePlaylist();
        std::istringstream data(snapshot()); std::string line;
        std::multiset<std::string> songs;
        std::getline(data, line);
        while (std::getline(data, line)) songs.insert(line);
        CHECK(songs == (std::multiset<std::string>{"A by one", "B by two", "C by three"}));
    }

    return 0;
}
