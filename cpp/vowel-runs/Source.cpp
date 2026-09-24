#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>

bool vowelCheck(char ch) {
    const int lower = std::tolower(static_cast<unsigned char>(ch));
    return lower == 'a' || lower == 'e' || lower == 'i' || lower == 'o' || lower == 'u';
}
int consecVowels(const std::string& word) {
    int run = 0, best = 0;
    for (char ch : word) {
        run = vowelCheck(ch) ? run + 1 : 0;
        best = std::max(best, run);
    }
    return best;
}
int main(int argc, char** argv) {
    if (argc > 2) { std::cerr << "Usage: vowel_runs [word-file]\n"; return 1; }
    std::ifstream input(argc == 2 ? argv[1] : "bigwords.txt");
    if (!input) { std::cerr << "Cannot open word file.\n"; return 1; }
    std::string word, best_word;
    int best = -1;
    while (input >> word) {
        int run = consecVowels(word);
        if (run > best) { best = run; best_word = word; }
    }
    if (input.bad() || best < 0) { std::cerr << "Word file is empty or unreadable.\n"; return 1; }
    std::cout << best_word << " (" << best << " consecutive vowels)\n";
    return 0;
}
