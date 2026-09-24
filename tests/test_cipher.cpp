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
#include "../cpp/word-cipher/main.cpp"
#undef main

int main() {

    const std::string ciphertext = ",vtaNm a_\"dabp!!";
    std::array<unsigned char, 16> bytes{};
    std::copy(ciphertext.begin(), ciphertext.end(), bytes.begin());
    CHECK(decrypt(bytes, 491) == "Attack at dawn!!");
    CHECK(decrypt(bytes, 0) == ciphertext);
    bytes.fill(0);
    CHECK(decrypt(bytes, 1) == std::string(16, static_cast<char>(0xff)));
    bytes.fill(0xff);
    const auto negative_word = decrypt(bytes, 1);
    for (std::size_t base = 0; base < 16; base += 4) {
        CHECK(static_cast<unsigned char>(negative_word[base]) == 0xfe);
        for (std::size_t i = 1; i < 4; ++i)
            CHECK(static_cast<unsigned char>(negative_word[base + i]) == 0xff);
    }
    bytes.fill(0);
    for (std::size_t i = 3; i < 16; i += 4) bytes[i] = 0x80;
    const auto signed_boundary = decrypt(bytes, 1);
    for (std::size_t base = 0; base < 16; base += 4) {
        for (std::size_t i = 0; i < 3; ++i)
            CHECK(static_cast<unsigned char>(signed_boundary[base + i]) == 0xff);
        CHECK(static_cast<unsigned char>(signed_boundary[base + 3]) == 0x7f);
    }

    return 0;
}
