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
#include "../cpp/movie-sort/Movie.cpp"
#undef main

int main() {

    Movie movies[4];
    CHECK(movies[0].getName() == "None" && movies[0].getRating() == "None");
    const std::string names[] = {"Zulu", "Alpha", "Beta", "Alpha"};
    for (int i = 0; i < 4; ++i) { movies[i].setName(names[i]); movies[i].setRating(names[i] + " rating"); }
    movies[0].sortAlphabetically(movies, 4);
    CHECK(movies[0].getName() == "Alpha" && movies[3].getName() == "Zulu");
    for (const auto& name : names) {
        bool found = false;
        for (auto& movie : movies) if (movie.getName() == name) {
            CHECK(movie.getRating() == name + " rating"); found = true;
        }
        CHECK(found);
    }
    movies[0].sortAlphabetically(nullptr, 0);
    expectThrow<std::invalid_argument>([&] { movies[0].sortAlphabetically(nullptr, 1); });
    expectThrow<std::invalid_argument>([&] { movies[0].sortAlphabetically(movies, -1); });

    return 0;
}
