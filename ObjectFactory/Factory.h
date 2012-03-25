//
//  Factory.h
//  ObjectFactory
//
//  Created by Ganesh M on 25/3/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#ifndef ObjectFactory_Factory_h
#define ObjectFactory_Factory_h


#include <iostream>
#include <map>
#include <typeinfo>

using namespace std;

template
<
    class AbstractProduct,
    typename IdentifierType,
    typename ProductCreator
>
class Factory
{
private:
    typedef std::map<IdentifierType, ProductCreator> AssocMap;
    AssocMap associations_;
    
public:
    static Factory& Instance()
    {
        static Factory myInstance_;
        return myInstance_;
    }
    
    bool Register(const IdentifierType id, ProductCreator creator)
    {
        std::cout << "Register - type identified " << id << std::endl;
        
        return associations_.insert(std::pair<IdentifierType, ProductCreator>(id, creator)).second;
    }
    
    AbstractProduct* CreateObject(const IdentifierType& id)
    {
        typename AssocMap::const_iterator i =
            associations_.find(id);
        if (i != associations_.end())
            return (i->second)();
        
        std::cout << "Invalid Identifier: " << id << std::endl;
        return NULL;
    }
};


#endif
