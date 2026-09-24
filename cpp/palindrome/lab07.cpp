#include <cctype>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <memory>
#include <stdexcept>

// Lab 7's pointer-and-length interface. The caller supplies length accessible bytes.
bool isPalindrome(char* p, int length) {
    if (length < 0 || (p == nullptr && length != 0))
        throw std::invalid_argument("Invalid character range");
    for (int i = 0; i < length / 2; ++i)
        if (*(p + i) != *(p + length - 1 - i)) return false;
    return true;
}
int main() {
    // Keep the dynamic 15-byte C-string; RAII also frees it on early exits.
    const auto cstr = std::make_unique<char[]>(15);
    char repeat;
    do {
        std::cout << "Enter a word of at most 14 characters: ";
        if (!(std::cin >> std::setw(15) >> cstr.get())) return 1;
        const int next = std::cin.peek();
        if (next != std::char_traits<char>::eof() &&
            !std::isspace(static_cast<unsigned char>(next))) {
            std::cerr << "Word exceeds the lab's 14-character limit.\n";
            return 1;
        }
        const int length = static_cast<int>(std::strlen(cstr.get()));
        std::cout << cstr.get() << " is " << (isPalindrome(cstr.get(), length) ? "" : "not ")
                  << "a palindrome.\n";
        std::cout << "Enter 'y' to repeat: ";
        if (!(std::cin >> repeat)) break;
    } while (repeat == 'y');
    return 0;
}
