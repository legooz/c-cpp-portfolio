#include <type_traits>
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
    static_assert(std::is_same_v<decltype(zipcode(0).getZipCode()), int>);
    CHECK(zipcode().getZipCode() == 0);
    CHECK(zipcode(99504).getBarCode() == "110100101000101011000010011");
    CHECK(zipcode("110100101000101011000010011").getZipCode() == 99504);
    for (int value = 0; value <= 99999; ++value) {
        const zipcode original(value);
        const auto barcode = original.getBarCode();
        CHECK(barcode.size() == 27);
        CHECK(original.getBarCode() == barcode); // Getter calls cannot accumulate output.
        for (std::size_t i = 1; i < 26; i += 5)
            CHECK(std::count(barcode.begin() + i, barcode.begin() + i + 5, '1') == 2);
        const zipcode decoded(barcode);
        CHECK(decoded.getZipCode() == value);
        CHECK(decoded.getBarCode() == barcode);
    }
    CHECK(zipcode(123).getBarCode().substr(1, 10) == "1100011000");
    for (int value : {-1, 100000, INT_MIN, INT_MAX})
        expectThrow<std::invalid_argument>([&] { (void)zipcode(value); });
    for (const std::string bad : {"", "1", "000000000000000000000000000", "111111111111111111111111111",
                                  "100000000000000000000000001", "11010010100010101100001001x"})
        expectThrow<std::invalid_argument>([&] { (void)zipcode(bad); });
    return 0;
}
