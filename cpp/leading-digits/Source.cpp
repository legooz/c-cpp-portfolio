#include <array>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

// Accept signed decimal integer tokens without overflowing machine integers.
// Zero has no nonzero leading digit and is omitted from the 1..9 histogram.
int leadingDigit(const std::string& token) {
    std::size_t start = (!token.empty() && (token[0] == '-' || token[0] == '+')) ? 1 : 0;
    if (start == token.size()) throw std::invalid_argument("Expected an integer");
    int first = 0;
    for (std::size_t i = start; i < token.size(); ++i) {
        if (token[i] < '0' || token[i] > '9') throw std::invalid_argument("Expected an integer");
        if (first == 0 && token[i] != '0') first = token[i] - '0';
    }
    return first;
}

int main(int argc, char** argv) {
    if (argc > 2) { std::cerr << "Usage: leading_digits [file]\n"; return 1; }
    std::ifstream input(argc == 2 ? argv[1] : "enrollments.txt");
    if (!input) { std::cerr << "Cannot open input file.\n"; return 1; }
    std::array<std::size_t, 10> counts{};
    std::string token;
    try {
        while (input >> token) ++counts[static_cast<std::size_t>(leadingDigit(token))];
    } catch (const std::invalid_argument& error) {
        std::cerr << error.what() << ": " << token << '\n'; return 1;
    }
    if (input.bad()) { std::cerr << "Input read failed.\n"; return 1; }
    for (std::size_t i = 1; i <= 9; ++i) std::cout << i << ": " << counts[i] << '\n';
    std::cout << "Zero values omitted: " << counts[0] << '\n';
    return 0;
}
