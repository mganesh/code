//
//  Lookup.h
//  BoostMultiIndex
//
//  Created by Ganesh M on 29/9/12.
//  Copyright (c) 2012 Ganesh M. All rights reserved.
//

#ifndef BoostMultiIndex_Lookup_h
#define BoostMultiIndex_Lookup_h


#include <iostream>
#include <string>

#include "Container.h"
#include "Instrument.h"

class Lookup {
public:
    
    Lookup() { }
    ~Lookup() { }
    
    bool Insert(const Instrument::pointer& ptr) {
        return m_instrument_set.insert(ptr).second;
    }
    
    template<typename T>
    void print(T* = 0)
    {
        print_out_by<T, instrument_set>(m_instrument_set);
    }
    
    template<typename T, typename Type>
    void find(const Type& s)
    {
        find_out_by<T, instrument_set>(m_instrument_set, s);
    }
    
    
private:
    instrument_set m_instrument_set;
};


#endif
