#include "zipcode.h"
#include <iostream>

int main() {
    const zipcode decoded("110100101000101011000010011");
    const zipcode encoded(99504);
    std::cout << "ZIP code: " << decoded.getZipCode() << '\n'
              << "Barcode: " << encoded.getBarCode() << '\n';
    return 0;
}
