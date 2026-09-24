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
#include "../cpp/zipcode-codec/zipcode.cpp"
#undef main

int main() {

    zipcode codec;
    CHECK(codec.getZipCode() == "00000");
    CHECK(codec.getBarCode(99504) == "110100101000101011000010011");
    // All five-digit values, including leading zeros; two bars per digit.
    for (int value = 0; value <= 99999; ++value) {
        std::string expected = std::to_string(value);
        expected.insert(0, 5 - expected.size(), '0');
        auto barcode = codec.getBarCode(value);
        CHECK(barcode.size() == 27);
        for (std::size_t i = 1; i < 26; i += 5)
            CHECK(std::count(barcode.begin() + i, barcode.begin() + i + 5, '1') == 2);
        CHECK(codec.getZipCode(barcode) == expected);
    }
    CHECK(zipcode(123).getZipCode() == "00123");
    CHECK(zipcode(codec.getBarCode(123)).getZipCode() == "00123");
    for (int value : {-1, 100000, INT_MIN, INT_MAX})
        expectThrow<std::invalid_argument>([&] { codec.getBarCode(value); });
    for (const std::string bad : {"", "1", "000000000000000000000000000", "111111111111111111111111111",
                                  "100000000000000000000000001", "11010010100010101100001001x"})
        expectThrow<std::invalid_argument>([&] { codec.getZipCode(bad); });

    return 0;
}
