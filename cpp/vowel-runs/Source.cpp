#include <algorithm>
#include <cctype>
#include <cstring>
#include <fstream>
#include <iostream>
#include <stdexcept>

constexpr std::size_t word_capacity = 14; // Handout: longest word is 13 characters.

bool vowelCheck(char ch) {
    const int lower = std::tolower(static_cast<unsigned char>(ch));
    return lower == 'a' || lower == 'e' || lower == 'i' || lower == 'o' || lower == 'u';
}
int consecVowels(const char* word) {
    int run = 0, best = 0;
    const auto length = std::strlen(word);
    for (std::size_t i = 0; i < length; ++i) {
        run = vowelCheck(word[i]) ? run + 1 : 0;
        best = std::max(best, run);
    }
    return best;
}
bool readWord(std::istream& input, char (&word)[word_capacity]) {
    input >> std::ws;
    if (input.peek() == std::char_traits<char>::eof()) return false;
    std::size_t length = 0;
    while (input.peek() != std::char_traits<char>::eof() &&
           !std::isspace(static_cast<unsigned char>(input.peek()))) {
        if (length == word_capacity - 1) throw std::length_error("Word exceeds the lab's 13-character limit");
        word[length++] = static_cast<char>(input.get());
    }
    word[length] = '\0';
    return true;
}
int main(int argc, char** argv) {
    if (argc > 2) { std::cerr << "Usage: vowel_runs [word-file]\n"; return 1; }
    std::ifstream input(argc == 2 ? argv[1] : "bigwords.txt");
    if (!input) { std::cerr << "Cannot open word file.\n"; return 1; }
    char word[word_capacity]{}, best_word[word_capacity]{};
    int best = -1;
    try {
        while (readWord(input, word)) {
            const int run = consecVowels(word);
            if (run > best) { best = run; std::strcpy(best_word, word); }
        }
    } catch (const std::length_error& error) {
        std::cerr << error.what() << '\n'; return 1;
    }
    if (input.bad() || best < 0) { std::cerr << "Word file is empty or unreadable.\n"; return 1; }
    std::cout << best_word << " (" << best << " consecutive vowels)\n";
    return 0;
}
