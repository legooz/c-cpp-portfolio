#include <iostream>
#include <string>
#include <string_view>

bool isPalindrome(std::string_view text) {
    for (std::size_t i = 0; i < text.size() / 2; ++i)
        if (text[i] != text[text.size() - 1 - i]) return false;
    return true;
}
int main() {
    std::string text;
    char repeat;
    do {
        std::cout << "Enter a word: ";
        if (!(std::cin >> text)) return 1;
        std::cout << text << " is " << (isPalindrome(text) ? "" : "not ") << "a palindrome.\n";
        std::cout << "Enter 'y' to repeat: ";
        if (!(std::cin >> repeat)) break;
    } while (repeat == 'y');
    return 0;
}
