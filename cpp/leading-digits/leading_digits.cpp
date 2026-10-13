#include "leading_digits.h"
#include <stdexcept>

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
