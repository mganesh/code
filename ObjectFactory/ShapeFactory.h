//
//  ShareFactory.h
//  ObjectFactory
//
//  Created by Ganesh M on 25/3/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#ifndef ObjectFactory_ShareFactory_h
#define ObjectFactory_ShareFactory_h

#include "Shape.h"
#include <map>
#include <iostream>

class Shape;

class ShapeFactory
{
public:
    typedef Shape* (*CreateShapeCallback)();

private:
    typedef std::map<int, CreateShapeCallback> CallbackMap;
    CallbackMap callbacks_;
    static ShapeFactory* pInstance_;

public:
    
    static ShapeFactory& Instance()
    {
        if (pInstance_ == NULL)
            pInstance_ = new ShapeFactory();
        
        return *pInstance_;
    }
    
    bool RegisterShape(int ShapeId, CreateShapeCallback createFn)
    {
        std::cout << "Register() - " << ShapeId << std::endl;
        return callbacks_.insert(CallbackMap::value_type(ShapeId, createFn)).second;
    }
    
    Shape* CreateShape(int ShapeId)
    {
        CallbackMap::const_iterator i = callbacks_.find(ShapeId);
        if (i == callbacks_.end())
        {
            std::cerr << "Invalid shape id:" << ShapeId << std::endl;
            return NULL;
        }
        
        return (i->second)();
    }
};


#endif
