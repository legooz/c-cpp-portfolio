#include <array>
#include <cstdint>
#include <climits>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <string>

// Cast through the character representation of a real int object, then back
// to its original type. Never dereference an int* into an unaligned char buffer.
static_assert(CHAR_BIT == 8 && sizeof(int) == 4 && INT_MIN == -2147483647 - 1,
              "This pointer exercise requires 32-bit two's-complement int");
std::string decrypt(const std::array<unsigned char, 16>& message, std::uint32_t key) {
    std::string result(16, '\0');
    for (std::size_t base = 0; base < message.size(); base += 4) {
        std::uint32_t encoded = 0;
        for (unsigned byte = 0; byte < 4; ++byte)
            encoded |= std::uint32_t{message[base + byte]} << (8 * byte);
        int storage = 0;
        char* characters = reinterpret_cast<char*>(&storage);
        std::memcpy(characters, &encoded, sizeof(storage));
        int* integer = reinterpret_cast<int*>(characters); // Back to the actual int object.
        const std::uint32_t word = static_cast<std::uint32_t>(*integer) - key;
        for (unsigned byte = 0; byte < 4; ++byte)
            result[base + byte] = static_cast<char>((word >> (8 * byte)) & 0xffU);
    }
    return result;
}
int main() {
    const std::string text = ",vtaNm a_\"dabp!!";
    std::array<unsigned char, 16> message{};
    for (std::size_t i = 0; i < message.size(); ++i) message[i] = static_cast<unsigned char>(text[i]);
    for (std::uint32_t key = 1; key <= 500; ++key) {
        std::cout << std::dec << key << ": ";
        for (unsigned char ch : decrypt(message, key)) {
            if (ch >= 32 && ch <= 126) std::cout << ch;
            else std::cout << "\\x" << std::hex << std::setw(2) << std::setfill('0') << unsigned(ch);
        }
        std::cout << '\n';
    }
    return 0;
}
