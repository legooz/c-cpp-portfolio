#include "zipcode.h"
#include <array>
#include <stdexcept>

namespace {
const std::array<std::string, 10> codes = {
    "11000", "00011", "00101", "00110", "01001",
    "01010", "01100", "10001", "10010", "10100"
};
}

zipcode::zipcode(int value) : value_(value) { (void)getBarCode(value); }
zipcode::zipcode(const std::string& barcode) : value_(std::stoi(getZipCode(barcode))) {}

std::string zipcode::getBarCode(int value) const {
    if (value < 0 || value > 99999) throw std::invalid_argument("ZIP must be in 00000..99999");
    std::string digits = std::to_string(value);
    digits.insert(0, 5 - digits.size(), '0');
    std::string result = "1";
    for (char digit : digits) result += codes[static_cast<std::size_t>(digit - '0')];
    return result + "1";
}

std::string zipcode::getZipCode(const std::string& barcode) const {
    if (barcode.size() != 27 || barcode.front() != '1' || barcode.back() != '1')
        throw std::invalid_argument("Barcode must have 27 bars with a 1 at each end");
    std::string result;
    for (std::size_t i = 1; i < 26; i += 5) {
        const auto part = barcode.substr(i, 5);
        std::size_t digit = 0;
        while (digit < codes.size() && codes[digit] != part) ++digit;
        if (digit == codes.size()) throw std::invalid_argument("Invalid 2-of-5 digit");
        result += static_cast<char>('0' + digit);
    }
    return result;
}

std::string zipcode::getZipCode() const { return getZipCode(getBarCode(value_)); }
std::string zipcode::getBarCode() const { return getBarCode(value_); }
