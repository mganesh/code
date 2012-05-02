#include <iostream>
#include <string>

class Base {
protected:
    std::string m_name;
public:
    Base()
        : m_name("Base") {
    }
    std::string name() const {
        return m_name;
    }
    virtual void display() const {
        std::cout << "Base::display()\n";
    }
};

class Derived : public Base {
    private:
    public:
        Derived() {
            m_name = "Derived";
        }
        std::string name() const {
            return m_name;
        }
        virtual void display() const {
            std::cout << "Derived::display()\n";
        }
};

/* Since the parameter b is passed by-value
 * as a Base, Derived class object will be
 * sliced off. Inside this function, b will
 * always act like an object of class Base
 */

void PrintAndDisplay(Base b) {
    std::cout << "Name: " << b.name() << std::endl;
    b.display();
}

/* The way around the slicing problem
 * is to pass b by reference-to-const
 */

void ConstPrintAndDisplay(const Base& b) {
     std::cout << "Name: " << b.name() << std::endl;
     b.display();
 }


int main() {
    Derived d;
    PrintAndDisplay(d);
    ConstPrintAndDisplay(d);
    return 0;
}
