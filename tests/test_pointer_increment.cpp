#include <climits>
#include <stdexcept>
#define main pointer_demo_main
#include "../cpp/palindrome/pointer_increment.cpp"
#undef main
#define CHECK(value) do { if (!(value)) throw std::runtime_error("Check failed: " #value); } while (false)
int main() {
    for (int value : {INT_MIN, -1, 0, INT_MAX - 1}) {
        int actual = value;
        addOne(&actual);
        CHECK(actual == value + 1);
    }
    int maximum = INT_MAX;
    bool overflow = false, invalid = false;
    try { addOne(&maximum); } catch (const std::overflow_error&) { overflow = true; }
    try { addOne(nullptr); } catch (const std::invalid_argument&) { invalid = true; }
    CHECK(overflow && invalid && maximum == INT_MAX);
    return 0;
}
