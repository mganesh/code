/*
 * =====================================================================================
 *
 *       Filename:  Int2Type.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/26/12 23:41:51
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ganesh Muniyandi (gm), ganesh.muniyandi@gmail.com
 *        Company:  Open Source
 *
 * =====================================================================================
 */

#include <iostream>
#include <map>
class MyClass {
private:
    typedef std::map<int, int> MyMap;
    MyMap ask;
    static MyMap bid;
    friend struct Int2Type;
public:
};

template<int n> struct Int2Type { };
template<>
struct MyClass::Int2Type<2>
{
    typedef MyMap::iterator first;
    enum { type = 2 };
};

template<>
struct MyClass::Int2Type<1> {
    enum { type = 1 };
};


int main() {
    enum {
        A,
        B
    };
    MyClass c;
    c.Int2Type<2>::first;
    return 0;
}
