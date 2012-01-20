//: C05:Factorial.cpp
// Compile-time computation using templates.
#include <iostream>
#include <cassert>
using namespace std;
 
template<int n> struct Factorial {
      enum { val = Factorial<n-1>::val * n };
};
 
template<> struct Factorial<0> {
      enum { val = 1 };
};
 
int main() {
      cout << Factorial<12>::val << endl; // 479001600

      /* To convince yourself that a 
         specialization of Factorial results 
         in the correct compile-time value, 
         you could use it as an array dimension
         */
      double nums[Factorial<5>::val];
      assert(sizeof nums == sizeof(double)*120);
} ///:~
