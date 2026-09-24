#pragma once
#include <charconv>
#include <cstring>
#include <random>
#include <stdexcept>

inline unsigned freshSeed() { return std::random_device{}(); }

// Assignment demonstrations vary by default; an explicit seed enables replay.
inline unsigned seedFromArguments(int argc, char** argv) {
    if (argc == 1) return freshSeed();
    if (argc != 2) throw std::invalid_argument("Expected at most one unsigned seed");
    unsigned seed;
    const char* end = argv[1] + std::strlen(argv[1]);
    const auto parsed = std::from_chars(argv[1], end, seed);
    if (parsed.ec != std::errc{} || parsed.ptr != end)
        throw std::invalid_argument("Seed must be an unsigned integer");
    return seed;
}
