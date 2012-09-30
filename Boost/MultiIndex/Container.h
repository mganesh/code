//
//  Container.h
//  BoostMultiIndex
//
//  Created by Ganesh M on 29/9/12.
//  Copyright (c) 2012 Ganesh M. All rights reserved.
//

#ifndef BoostMultiIndex_Container_h
#define BoostMultiIndex_Container_h

#include <iostream>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/shared_ptr.hpp>

#include "Instrument.h"

using boost::multi_index_container;
using namespace boost::multi_index;

struct externalid { };
struct internalid { };
struct Id { };

typedef multi_index_container<
    Instrument::pointer,
    indexed_by<
        ordered_unique< tag<externalid>,  mem_fun<Instrument, std::string, &Instrument::ExternalId> >,
        ordered_unique< tag<internalid>,  mem_fun<Instrument, std::string, &Instrument::InternalId> >,
        ordered_unique< tag<Id>,          identity<Instrument>, InstrumentIdCompare>
    >
> instrument_set;


template<typename Tag,typename MultiIndexContainer>
void print_out_by(
                  const MultiIndexContainer& s,
                  Tag* =0 /* fixes a MSVC++ 6.0 bug with implicit template function parms */
                  )
{
    /* obtain a reference to the index tagged by Tag */
    
    const typename boost::multi_index::index<MultiIndexContainer,Tag>::type& i=
    get<Tag>(s);
    
    typedef typename MultiIndexContainer::value_type value_type;
    
    /* dump the elements of the index to cout */
    
    std::copy(i.begin(),i.end(),std::ostream_iterator<value_type>(std::cout));
    
}


template<typename Tag,typename MultiIndexContainer, typename Type>
void find_out_by(
            const MultiIndexContainer& s,
                 const Type& ss
        )
{
    /* obtain a reference to the index tagged by Tag */
    
    const typename boost::multi_index::index<MultiIndexContainer,Tag>::type& i=
    get<Tag>(s);
        
    typename boost::multi_index::index<MultiIndexContainer,Tag>::type::iterator it = i.find(ss);
    
    if (it != i.end())
    {
        std::cout << "Found Search (";
        std::cout << *it;
        std::cout << ")" << std::endl;
    }
    else {
        std::cerr << "Not found !!\n";
    }
    
    std::cout << "\n The End !!\n";
}


#endif
