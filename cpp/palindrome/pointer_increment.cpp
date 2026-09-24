#include <iostream>
#include <limits>
#include <stdexcept>

// Recovered from the commented-out Lab 7 part 1 in the archived source.
void addOne(int* ptrNum) {
    if (ptrNum == nullptr) throw std::invalid_argument("Expected an integer pointer");
    if (*ptrNum == std::numeric_limits<int>::max()) throw std::overflow_error("Integer overflow");
    *ptrNum += 1;
}
int main() {
    int number = 0;
    std::cout << number << '\n';
    addOne(&number);
    std::cout << number << '\n';
    return 0;
}
