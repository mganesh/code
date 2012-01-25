/*
 * =====================================================================================
 *
 *       Filename:  unique_chars.cc
 *
 *    Description:  Algorithm to determine if a string has all unique chars
 *
 *        Version:  1.0
 *        Created:  01/26/12 00:31:30
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ganesh Muniyandi (gm), ganesh.muniyandi@gmail.com
 *        Company:  Open Source
 *
 * =====================================================================================
 */

#include <iostream>
#include <string.h>
#include <bitset>
#define ASCII_SIZE 256

bool isUniqueChar1(const std::string& input) {
    if (input.length() > ASCII_SIZE) return false;

    bool boolean[ASCII_SIZE];
    const char* pString = input.c_str();
    memset(boolean, 0, ASCII_SIZE-1);
    for(int i=0; i<input.size(); ++i) {
        int index = static_cast<int>(*pString);
        if (boolean[index]) return false;
        boolean[index] = true;
        ++pString;
    }
    return true;
}

bool isUniqueChar2(const std::string& input) {
    if (input.length() > ASCII_SIZE) return false;

    std::bitset<ASCII_SIZE> myBits;
    myBits.reset();
    const char* pString = input.c_str();
    for(int i=0; i<input.size(); ++i) {
        int index = static_cast<int>(*pString);
        if (myBits.test(index)) return false;
        myBits.set(index);
        ++pString;
    }
    return true;
}

int main() {
    std::string i1("UNIQE");
    std::string i2("REPEATED");

    std::cout << i1 << " has " << (isUniqueChar1(i1) ? "unique " : "repeated " ) << "chars." << std::endl;
    std::cout << i2 << " has " << (isUniqueChar1(i2) ? "unique " : "repeated " ) << "chars." << std::endl;

    std::cout << i1 << " has " << (isUniqueChar2(i1) ? "unique " : "repeated " ) << "chars." << std::endl;
    std::cout << i2 << " has " << (isUniqueChar2(i2) ? "unique " : "repeated " ) << "chars." << std::endl;

    return 0;
}
