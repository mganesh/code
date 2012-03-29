//
//  main.cpp
//  Boost
//
//  Created by Ganesh M on 27/3/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <boost/utility/enable_if.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/type_traits.hpp>

template<typename T>
struct id { typedef T type; };

id<char[1]>::type &find_etype(int);
id<char[2]>::type &find_etype(unsigned int);
id<char[3]>::type &find_etype(long);
id<char[4]>::type &find_etype(unsigned long);

template<int> struct get_etype;
template<> struct get_etype<1> { typedef int type; };
template<> struct get_etype<2> { typedef unsigned int type; };
template<> struct get_etype<3> { typedef long type; };
template<> struct get_etype<4> { typedef unsigned long type; };
template<> struct get_etype<5> { typedef double type; };

template <typename T>
typename boost::disable_if< boost::is_enum<T>, bool>::type 
ConvertString(const std::string& theString, T& theResult)
{
    std::istringstream iss(theString);
    return !(iss >> theResult).fail();
}

template <typename T>
typename boost::enable_if< boost::is_enum<T>, bool>::type 
ConvertString(const std::string& theString, T& theResult)
{
    typedef typename get_etype<sizeof find_etype(theResult)>::type 
    safe_type;
    
    std::istringstream iss(theString);
    safe_type temp;
    const bool isValid = !(iss >> temp).fail();
    theResult = static_cast<T>(temp);
    return isValid;
}


int main (int argc, const char * argv[])
{
    double _double;
    int _int;
    unsigned int _uint;
    unsigned long _ulong;
    
    bool r1 = ConvertString("1023.12", _double);
    bool r2 = ConvertString("101", _int);
    bool r3 = ConvertString("10100000", _uint);
    bool r4 = ConvertString("1010000000", _ulong);
    
    std::cout << "Result: " << r1 << ", Value: " << _double << std::endl;
    std::cout << "Result: " << r2 << ", Value: " << _int << std::endl;
    std::cout << "Result: " << r3 << ", Value: " << _uint << std::endl;
    std::cout << "Result: " << r4 << ", Value: " << _ulong << std::endl;
    
    return 0;
}

