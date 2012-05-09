#include <iostream>
#include <stdint.h>
#include <cassert>
using namespace std;
 
template<uint64_t n> 
struct Factorial {
      static const uint64_t val = Factorial<n-1>::val * n; 
};
 
template<> struct Factorial<0> {
      static const uint64_t val = 1;
};
 
int main() {
    cout << Factorial<12>::val << endl; // 479001600
    return 0;
}
