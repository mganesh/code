//
//  main.cpp
//  ObjectFactory
//
//  Created by Ganesh M on 25/3/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Factory.h"
#include "Shape.h"


int main (int argc, const char * argv[])
{
    typedef Factory<Shape, std::string, Shape::CreateShapeCallback> FactoryType;
    std::cout << "Main()" << std::endl;

    Shape* p1 = FactoryType::Instance().CreateObject("LINE");
    
    Shape* p2 = FactoryType::Instance().CreateObject("CIRCLE");
    
    if (p1)
        p1->Name();
    else
        std::cout << "Fix me !!" << std::endl;
    
    if (p2)
        p2->Name();
    else
        std::cout << "Fix me !!" << std::endl;
    
    std::cout << "The End !!" << std::endl;
    
    return 0;
}

