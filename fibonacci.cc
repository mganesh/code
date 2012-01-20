//: C05:Fibonacci.cpp
#include <iostream>
 
template<int n> struct Fib {
    enum { val = Fib<n-1>::val + Fib<n-2>::val };
};
 
template<> struct Fib<1> { enum { val = 1 }; };
 
template<> struct Fib<0> { enum { val = 0 }; };
 
int main() {
    std::cout << Fib<5>::val << std::endl;   // 6
    std::cout << Fib<20>::val << std::endl;  // 6765
} ///:~
