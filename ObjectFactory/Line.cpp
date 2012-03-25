//
//  Line.cpp
//  ObjectFactory
//
//  Created by Ganesh M on 25/3/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Line.h"
#include "Factory.h"

const std::string Line::LINE = "LINE";
const bool Line::registered = FactoryType::Instance().Register(Line::LINE, CreateLine);
Shape* Line::CreateLine()
{
    return new Line();
}

