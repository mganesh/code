#include <iostream>
#include <limits.h>
#include <functional>

class noncopyable {

protected:
    noncopyable() { std::cout << "noncopyable .. \n"; }
    ~noncopyable() { std::cout << "~noncopyable .. \n"; }
private:
    noncopyable(const noncopyable&);
    noncopyable& operator=(const noncopyable&);
};

class myclass : private noncopyable {
    
    
public:
    myclass() { std::cout << "MyClass ..\n"; }
    myclass(std::string name) 
    : m_name(name) {
    
    }
    ~myclass() { std::cout << "~MyClass ..\n"; }
private:
    std::string m_name;
};


int main()
{
    myclass* ptr = new myclass();
    delete ptr;
    return 0;
}
