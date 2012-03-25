//
//  Circle.h
//  ObjectFactory
//
//  Created by Ganesh M on 25/3/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#ifndef ObjectFactory_Circle_h
#define ObjectFactory_Circle_h

#include "Shape.h"

class Circle : public Shape
{
public:
    Circle()
    : Shape("Circle")
    {
        std::cout << "Circle() - Created .. " << std::endl;
    }
    
    static Shape* CreateCircle();
private:
    static const std::string CIRCLE;
    static const bool registerted;
    
};

#endif
