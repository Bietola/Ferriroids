#include "utils.h"

//take an integer and build a fixed digit string out of it (with 0s where there are usually no digits)
std::string utils::intToFixedDigitsString(int num, int digits) {
    assert(digits > 0);

    std::string retVal;

    int numDigits = 0;
    for(int tmp = num; tmp != 0; tmp /= 10)
        numDigits++;

    if(numDigits > digits) {
        for(int j = 0; j < digits; j++)
            retVal += "9";
        return retVal;
    }

    else {
        for(int j = numDigits; j < digits; j++)
        retVal += "0";

        return retVal + std::to_string(num);
    }
}
