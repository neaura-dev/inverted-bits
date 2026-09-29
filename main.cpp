#include <iostream>

using namespace std;

union InputNumber {
    short int shortIntNumber;
    unsigned short usNumber;
    double doubleNumber;
    unsigned long long ullNumber;
};

//  Bits printer X16
void printBitsX16(unsigned short number) {
    for (int i = 15; i >= 0; i--) {
        cout << ((number >> i) & 1);
        if (i == 15) {
            cout << ' ';
        }
    }
}

// Bits printer X64
void printBitsX64(unsigned long long number) {
    for (int i = 63; i >= 0; i--) {
        cout << ((number >> i) & 1);
        if (i == 63 || i == 52) {
            cout << ' ';
        }
    }
}

// Inverted mask maker
unsigned long long makeMask(int count, int lowBit) {
    return ((1ull << count) - 1ull) << lowBit;
}

int main() {
    
    // Type select
    cout << "Select type of number (0 - short int, 1 - double): ";
    bool numberType;
    cin >> numberType;

    // Number input
    cout << "Enter ";
    if (!numberType) {
        cout << "short int";
    }
    else {
        cout << "double";
    }
    cout << " number: ";
    InputNumber userNumber;
    if (!numberType) {
        cin >> userNumber.shortIntNumber;
    }
    else {
        cin >> userNumber.doubleNumber;
    }

    // Conditions input
    cout << "Enter count of bits that will be inverted: ";
    int countOfBits;
    cin >> countOfBits;
    cout << "Enter the high bit of the group that will be inverted: ";
    int highBit;
    cin >> highBit;
    int lowBit = highBit - countOfBits + 1;
    if (lowBit < 0) {
        cout << "Error! Too many bits!";
        return -1;
    }
    if ((!numberType && highBit > 15) || (numberType && highBit > 63)) {
        cout << "Error! The high bit is too high!";
        return -2;
    }

    // Output
    cout << "Number: ";
    if (!numberType) {
        cout << userNumber.shortIntNumber;
    }
    else {
        cout << userNumber.doubleNumber;
    }
    cout << endl;
    cout << "Number's bits: ";
    if (!numberType) {
        printBitsX16(userNumber.usNumber);
    }
    else {
        printBitsX64(userNumber.ullNumber);
    }
    cout << endl << endl;
    cout << "Mask: ";
    if (!numberType) {
        unsigned short mask = (unsigned short)makeMask(countOfBits, lowBit);
        printBitsX16(mask);
        userNumber.usNumber = userNumber.usNumber ^ mask;
    }
    else {
        unsigned long long mask = makeMask(countOfBits, lowBit);
        printBitsX64(mask);
        userNumber.ullNumber = userNumber.ullNumber ^ mask;
    }
    cout << endl << endl;
    cout << "Inverted bits: ";
    if (!numberType) {
        printBitsX16(userNumber.usNumber);
    }
    else {
        printBitsX64(userNumber.ullNumber);
    }
    cout << endl << "Inverted number: ";
    if (!numberType) {
        cout << userNumber.shortIntNumber;
    }
    else {
        cout << userNumber.doubleNumber;
    }
    
    return 0;
}