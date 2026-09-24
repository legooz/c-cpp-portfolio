#pragma once
#include <string>

// Assignment format: frame bars plus five 2-of-5 digits; no checksum.
class zipcode {
public:
    zipcode() = default;
    explicit zipcode(int value);
    explicit zipcode(const std::string& barcode);
    int getZipCode() const;
    std::string getBarCode() const;
private:
    static int decode(const std::string& barcode);
    static std::string encode(int value);
    int value_ = 0; // Only one stored representation, as required.
};
