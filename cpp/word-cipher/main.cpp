#include <array>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <string>

// Explicit little-endian unsigned words avoid aliasing, alignment and signed
// overflow problems. This is a reversible classroom exercise, not encryption.
std::string decrypt(const std::array<unsigned char, 16>& message, std::uint32_t key) {
    std::string result(16, '\0');
    for (std::size_t base = 0; base < message.size(); base += 4) {
        std::uint32_t word = 0;
        for (unsigned byte = 0; byte < 4; ++byte)
            word |= std::uint32_t{message[base + byte]} << (8 * byte);
        word -= key;
        for (unsigned byte = 0; byte < 4; ++byte)
            result[base + byte] = static_cast<char>((word >> (8 * byte)) & 0xffU);
    }
    return result;
}
int main() {
    const std::string text = ",vtaNm a_\"dabp!!";
    std::array<unsigned char, 16> message{};
    for (std::size_t i = 0; i < message.size(); ++i) message[i] = static_cast<unsigned char>(text[i]);
    for (std::uint32_t key = 0; key <= 500; ++key) {
        std::cout << std::dec << key << ": ";
        for (unsigned char ch : decrypt(message, key)) {
            if (ch >= 32 && ch <= 126) std::cout << ch;
            else std::cout << "\\x" << std::hex << std::setw(2) << std::setfill('0') << unsigned(ch);
        }
        std::cout << '\n';
    }
    return 0;
}
