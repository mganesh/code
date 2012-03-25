//
//  Shape.h
//  ObjectFactory
//
//  Created by Ganesh M on 25/3/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#ifndef ObjectFactory_Shape_h
#define ObjectFactory_Shape_h

#include "Factory.h"

class Shape
{
private:
    std::string m_Name;
    
public:
    Shape(std::string name)
    : m_Name(name)
    {
        
    }
    void Name()
    {
        std::cout << "Type: " << m_Name << std::endl;
    }
    
    
    typedef Shape* (*CreateShapeCallback)();
    typedef Factory<Shape, std::string, CreateShapeCallback> FactoryType;
};

#endif
