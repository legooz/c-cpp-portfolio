#include <iostream>
#include <string>
#include "zipcode.h"

using namespace std;

int main()
{

    //cout << "Knowing that the bar code starts and end with a one please enter the numbers between them" << endl;

    //decodes to 99504
    string barCodeBinary = "110100101000101011000010011";
    cout << "Bar code inputed." << endl;
    zipcode zip;
    cout << "getZipCode : " << zip.getZipCode(barCodeBinary) << endl;

    //encodes to "110100101000101011000010011"
    int zipCodeEncode = 99504;
    cout << "Zip code inputed." << endl;
    zipcode zip2;
    cout << "getbarCode : " << zip2.getBarCode(zipCodeEncode) << endl;

    return 0;
    return 0;
}
