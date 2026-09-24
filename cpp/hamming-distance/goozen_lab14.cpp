#include <bitset>
#include <charconv>
#include <cstdint>
#include <iostream>
#include <string>

unsigned countBitsSetToOne(std::uint32_t n) {
    unsigned count = 0;
    while (n) { count += n & 1U; n >>= 1U; }
    return count;
}
static bool readCode(std::uint32_t& value) {
    std::string token;
    if (!(std::cin >> token)) return false;
    auto result = std::from_chars(token.data(), token.data() + token.size(), value);
    return result.ec == std::errc{} && result.ptr == token.data() + token.size();
}
int main() {
    std::uint32_t first, second;
    if (!readCode(first) || !readCode(second)) {
        std::cerr << "Expected two unsigned 32-bit decimal integers.\n"; return 1;
    }
    const auto difference = first ^ second;
    std::cout << std::bitset<32>(first) << '\n' << std::bitset<32>(second) << '\n'
              << "Differing bits: " << std::bitset<32>(difference) << '\n'
              << "Hamming distance: " << countBitsSetToOne(difference) << '\n';
    return 0;
}
