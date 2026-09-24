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
#include "../cpp/palindrome/lab07.cpp"
#undef main

int main() {

    CHECK(isPalindrome("")); CHECK(isPalindrome("a")); CHECK(isPalindrome("abba"));
    CHECK(isPalindrome("racecar")); CHECK(!isPalindrome("ab")); CHECK(!isPalindrome("Abba"));
    CHECK(isPalindrome(std::string(100000, 'x')));

    return 0;
}
