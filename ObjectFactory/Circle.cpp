//
//  Circle.cpp
//  ObjectFactory
//
//  Created by Ganesh M on 25/3/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Circle.h"
#include "Factory.h"

const std::string Circle::CIRCLE = "CIRCLE";

const bool Circle::registerted = FactoryType::Instance().Register(Circle::CIRCLE, CreateCircle);

Shape* Circle::CreateCircle()
{
    return new Circle();
}