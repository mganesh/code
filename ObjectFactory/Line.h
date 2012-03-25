//
//  Line.h
//  ObjectFactory
//
//  Created by Ganesh M on 25/3/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#ifndef ObjectFactory_Line_h
#define ObjectFactory_Line_h

#include "Shape.h"

class Line : public Shape
{
public:
    
    Line()
    : Shape("Line")
    {
        std::cout << "Line() Created .. " << std::endl;
    }
    
    static Shape* CreateLine();

private:
    static const std::string LINE;
    static const bool registered;

};

#endif
