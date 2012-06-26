#include <iostream>
#include <sstream>
#include <cstdlib> // for rand() and srand()
#include <limits>
#include <stdint.h>
#include <set>
#include <map>
#include <assert.h>
#include "Test.h"
#include <exception>

namespace {
    const std::string Action = "AXMMAXMXAXAMXMA";
	const std::string Side   = "SBBSSBBSSBBSSBB";
}

namespace test {

    uint64_t Test::GetRandom() {
        
        while (1) {
            m_lastRandom = (m_low + rand() %(m_high-m_low+1));
            value_type r = m_URandoms.insert(m_lastRandom);
            if (r.second) return m_lastRandom;
            
            if (m_URandoms.size() >= m_nTestCases) {
                throw "Out of Range !!";
            }
        }
    }

bool Test::Next(std::ostream& line) {
    
    if (++m_Count >= m_nTestCases)
        return false;
    try {
        std::ostringstream oss;
        uint8_t index = GetRandom()%(Side.size()-1);
        switch (Action[index]) {
            case 'M':
                oss << ModifyOrderMsg();
                break;
            case 'X':
                oss << RemoveOrderMsg();
                break;
            case 'A':
            {
                if (Side[index] == 'S')
                    oss << SellOrderMsg();
                else if (Side[index] == 'B')
                    oss << BuyOrderMsg();
                break;
            }
            default:
                assert(NULL);
                break;
        }
        line << oss.str();
    } catch (...) {
        return false;
    }
    return true;
}

void Test::AutoPlay(std::ostream& os, bool debug) {
    for(int i=0; i< m_nTestCases-1; ++i) {
        if (Next(os) == false)
            return;
        os << std::endl;
    }
}
	
uint64_t Test::NextRandom() {
	
	while (1) {
		m_lastRandom = (m_low + rand() %(m_high-m_low+1));
		value_type r = m_URandoms.insert(m_lastRandom);
		if (r.second) return m_lastRandom;
		if (m_URandoms.size() >= m_nTestCases)
			throw "Out of Range";
	}
}

float Test::rand_float(float low, float high) {
    return ((high-low)*((float)rand()/RAND_MAX))+low;
}

int64_t Test::GetUniqueNo() { return ++m_unique; }
    
template<typename T>
Test::Lookup::iterator Test::GetNthElement(T &maps, uint64_t pos) {
    assert (pos >= 0);
    assert (maps.size() >= (size_t)pos);
    
    typename T::iterator i = maps.start();
    std::advance(i, pos);
    return i;
}

std::string Test::BuyOrderMsg() {
    Data* _data = new Data();
    _data->price = rand_float(m_bid_low, m_bid_high);
    _data->size = (m_lastRandom%100); // max 100;
    _data->id = GetUniqueNo();
    _data->side = 'B';
    
    m_Bids.insert(Lookup::value_type(_data->id, _data));
    std::ostringstream oss;
    oss << "A,"
    << _data->id << ","
    << "B,"
    << _data->size << ","
    << _data->price;
    
    return oss.str();
}
    
std::string Test::SellOrderMsg() {
    Data* _data = new Data();
    _data->price = rand_float(m_ask_low, m_ask_high);
    _data->size = (m_lastRandom%100); // max 100;
    _data->id = GetUniqueNo();
    _data->side = 'S';
    
    m_Asks.insert(Lookup::value_type(_data->id, _data));
    std::ostringstream oss;
    oss << "A,"
    << _data->id << ","
    << "S,"
    << _data->size << ","
    << _data->price;
    
    return oss.str();
}

template<typename T>
test::Data* Test::GetRandomData(T &maps) {
    
    uint64_t index = (m_lastRandom%(maps.size()));
    
    typename T::iterator it = maps.begin();
    assert(index >= 0);
    assert(maps.size() >= (size_t)index);
    std::advance(it, index);
    
    return it->second;
}
    
template<typename T>
test::Data* Test::ModifyData(T &maps, bool bid) {
    
    uint64_t index = (m_lastRandom%(maps.size()));
    
    typename T::iterator it = maps.begin();
    assert(index >= 0);
    assert(maps.size() >= (size_t)index);
    std::advance(it, index);
    
    Data *data = it->second;
    if (index%3) {
        data->size = (m_lastRandom%100); 
    } else if (bid) {
        data->price = rand_float(m_ask_low, m_ask_high);
    } else {
        data->price = rand_float(m_bid_low, m_bid_high);
    }
    
    return data;
}
    
std::string Test::ModifyOrderMsg() {
    bool ask = m_lastRandom%2;
    Data* data = NULL;
    if (ask && m_Asks.size()) {
        data = ModifyData<Lookup>(m_Asks, false);
    } else if (m_Bids.size()) {
        data = ModifyData<Lookup>(m_Bids, true);
    }
    
    std::ostringstream oss;
    if (data) {
        oss << "M,"
        << data->id << ","
        << data->side << ","
        << data->size << ","
        << data->price;
    } else {
        // no orderbook. generate some illegal order
        uint64_t id = GetUniqueNo();
        oss << "M,"
            << id << ","
            << (id%2 ? "B," : "S,")
            << (id%100) << ","
            << rand_float(100, 140);
    }
    
    return oss.str();
}

std::string Test::RemoveOrderMsg() {
    bool ask = m_lastRandom%2;
    Data* data = NULL;
    if (ask && m_Asks.size()) {
        data = GetRandomData<Lookup>(m_Asks);
    } else if (m_Bids.size()) {
        data = GetRandomData<Lookup>(m_Bids);
    }
    
    std::ostringstream oss;
    if (data) {
        oss << "X,"
        << data->id << ","
        << data->side << ","
        << data->size << ","
        << data->price;
    } else {
        // no orderbook. generate some illegal order
        uint64_t id = m_unique;
        oss << "X,"
        << id << ","
        << (id%2 ? "B," : "S,")
        << (id%100) << ","
        << rand_float(100, 140);

    }
    
    return oss.str();
}

}/* namespace */

int main() {
    test::Test t;
    t.AutoPlay(std::cout);
}
