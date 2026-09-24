#include <charconv>
#include <cstring>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <vector>

long long checkedProduct(const std::vector<long long>& values) {
    bool negative = false;
    for (auto value : values) {
        if (value == 0) return 0;
        if (value < 0) negative = !negative;
    }
    const auto max = static_cast<unsigned long long>(std::numeric_limits<long long>::max());
    const auto limit = max + (negative ? 1ULL : 0ULL);
    unsigned long long magnitude = 1;
    for (auto value : values) {
        // Avoid negating LLONG_MIN. All nonzero integer magnitudes are at least 1.
        const auto factor = value < 0 ? static_cast<unsigned long long>(-(value + 1)) + 1ULL
                                      : static_cast<unsigned long long>(value);
        if (magnitude > limit / factor)
            throw std::overflow_error("Product exceeds signed 64-bit range");
        magnitude *= factor;
    }
    if (negative && magnitude == max + 1ULL) return std::numeric_limits<long long>::min();
    return negative ? -static_cast<long long>(magnitude) : static_cast<long long>(magnitude);
}
int main(int argc, char** argv) {
    if (argc < 2) { std::cerr << "Usage: command_product INT...\n"; return 1; }
    std::vector<long long> values;
    for (int i = 1; i < argc; ++i) {
        const char* text = argv[i];
        if (*text == '+') {
            ++text;
            if (*text == '-') { std::cerr << "Invalid integer sign.\n"; return 1; }
        }
        long long value;
        const auto end = text + std::strlen(text);
        const auto result = std::from_chars(text, end, value);
        if (result.ec != std::errc{} || result.ptr != end) {
            std::cerr << "Expected signed 64-bit integers.\n"; return 1;
        }
        values.push_back(value);
    }
    try {
        std::cout << checkedProduct(values) << '\n';
    } catch (const std::overflow_error& error) {
        std::cerr << error.what() << '\n'; return 1;
    }
    return 0;
}
