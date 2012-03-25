/*
 * =====================================================================================
 *
 *       Filename:  TrailingZeros.cc
 *
 *    Description:  Program to find number of trailing zeros
 *
 *        Version:  1.0
 *        Created:  01/26/12 12:05:55
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ganesh Muniyandi (gm), ganesh.muniyandi@gmail.com
 *        Company:  Open Source
 *
 * =====================================================================================
 */
#include <iostream>
unsigned int NTrailingZeros(unsigned int N) {
    unsigned int result = 0;
    unsigned int divisor = 5;
    while(true) {
        unsigned int t = N / divisor;
        if (!t) break;
        result += t;
        divisor *= 5;
    }
    return result;
}

int main() {

    for(unsigned int i=0; i<1000000000; ++i)
        std::cout << i << " ==> " << NTrailingZeros(i) << std::endl;

    return 0;
}
