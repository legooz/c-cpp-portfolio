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
#include <type_traits>
#define CHECK(condition) do { if (!(condition)) throw std::runtime_error("Check failed: " #condition); } while (false)
template<class Exception, class Function> void expectThrow(Function operation) {
    bool caught = false;
    try { operation(); } catch (const Exception&) { caught = true; }
    CHECK(caught);
}

#define main demo_main_0
#include "../cpp/palindrome/lab07.cpp"
#undef main

int main() {

    static_assert(std::is_same_v<decltype(&isPalindrome), bool (*)(char*, int)>);
    for (std::string text : {"", "a", "abba", "racecar"})
        CHECK(isPalindrome(text.data(), static_cast<int>(text.size())));
    for (std::string text : {"ab", "Abba"})
        CHECK(!isPalindrome(text.data(), static_cast<int>(text.size())));
    std::string large(100000, 'x');
    CHECK(isPalindrome(large.data(), static_cast<int>(large.size())));
    char unterminated[] = {'a', 'b', 'b', 'a'};
    CHECK(isPalindrome(unterminated, 4)); // Function uses the supplied length.
    CHECK(isPalindrome(nullptr, 0));
    expectThrow<std::invalid_argument>([] { isPalindrome(nullptr, 1); });
    expectThrow<std::invalid_argument>([&] { isPalindrome(unterminated, -1); });

    return 0;
}
