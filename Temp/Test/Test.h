/*
 *  Test.h
 *  
 *
 *  Created by Ganesh M on 6/25/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include <limits>
#include <stdint.h>
#include <set>
#include <map>
#include <string>
#include <cstdlib> // for rand() and srand()

namespace {
	static const uint64_t int_max = std::numeric_limits<int>::max();
	static const short short_max = std::numeric_limits<short>::max();

}

namespace test {

struct Data {
	int64_t id;
	double price;
	int16_t size;
    char side;
};
	
class Test {
	
private:
	uint64_t m_low;
	uint64_t m_high;
	uint64_t m_unique;
	uint64_t m_lastRandom;
    uint64_t m_Count;
	
	typedef std::set<uint64_t> UniqueRandoms;
	UniqueRandoms m_URandoms;
	typedef std::pair<UniqueRandoms::iterator, bool>value_type;
	
	typedef std::map<uint64_t, Data*> Lookup;
	Lookup m_Bids;
	Lookup m_Asks;
    
    double m_bid_low;
    double m_bid_high;
    
    double m_ask_low;
    double m_ask_high;
    
    uint64_t m_nTestCases;
	
public:
	explicit Test(uint32_t n = short_max
                  , uint64_t low=0
				  , uint64_t high=int_max)
			: m_low(low)
			, m_high(high)
			, m_unique(0)
			, m_lastRandom(0)
            , m_Count(0)
            , m_bid_low(100.0)
            , m_bid_high(120.0)
            , m_ask_low(120.5)
            , m_ask_high(140)
            , m_nTestCases(n)
	{
		srand(time(0));
	}
	
	bool Next(std::ostream&);
    void AutoPlay(std::ostream&);
	
private:
	uint64_t NextRandom();
	std::string BuyOrderMsg();
	std::string SellOrderMsg();
	std::string ModifyOrderMsg();
	std::string RemoveOrderMsg();
    
	float rand_float(float a, float b);
	int64_t GetUniqueNo();
    uint64_t GetRandom();

    template<typename T>
    Lookup::iterator GetNthElement(T& maps, uint64_t pos);
	
    template<typename T>
    Data* ModifyData(T& maps, bool);
    
    template<typename T>
    Data* GetRandomData(T& maps);
};
}
