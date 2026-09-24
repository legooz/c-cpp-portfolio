#pragma once
#include <string>

// Teaching format: frame bars and five 2-of-5 digits; no postal checksum.
class zipcode {
public:
    zipcode() = default;
    explicit zipcode(int value);
    explicit zipcode(const std::string& barcode);
    std::string getZipCode(const std::string& barcode) const;
    std::string getBarCode(int value) const;
    std::string getZipCode() const;
    std::string getBarCode() const;
private:
    int value_ = 0;
};
