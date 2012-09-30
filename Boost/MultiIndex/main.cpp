//
//  main.cpp
//  BoostMultiIndex
//
//  Created by Ganesh M on 29/9/12.
//  Copyright (c) 2012 Ganesh M. All rights reserved.
//

#include <iostream>
#include <string>
#include <boost/shared_ptr.hpp>
#include "Instrument.h"
#include "Lookup.h"

int main(int argc, const char * argv[])
{

    // insert code here...
    std::cout << "Hello, World!\n";
    Lookup m_Lookup;
    
    Instrument* ptr = NULL;
    {
        ptr = new Instrument("A", "D");
        ptr->SetId(InstrumentId("FGBLZ2", "BTEC", 1));
        m_Lookup.Insert(Instrument::pointer(ptr));
        
    }
    InstrumentId instrument_id("FGBLZ2", "BTEC", 1);
    {
        ptr = new Instrument("C", "B");
        ptr->SetId(InstrumentId("FGBLZ3", "BTEC", 1));
        m_Lookup.Insert(Instrument::pointer(ptr));
        
    }
    m_Lookup.print<externalid>();
    //m_Lookup.find<externalid>("A");
    m_Lookup.find<Id>(instrument_id);
    
    return 0;
}

