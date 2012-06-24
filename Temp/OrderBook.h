//
//  OrderBook.h
//  ExchangeFeed
//
//  Created by Ganesh M on 20/6/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#ifndef ExchangeFeed_OrderBook_h
#define ExchangeFeed_OrderBook_h

#include <map>
#include <string>
#include "Order.h"
#include "Exceptions.h"

namespace feed {
    
class OrderBook {
public:
    explicit OrderBook(const std::string& symbol);
    ~OrderBook();
    
private:
    typedef std::multimap<double, Order* > GenericOrders;
    typedef GenericOrders::iterator pos;
    
    typedef std::multimap<double, Order*, std::greater<double> > BidOrders;
    typedef std::multimap<double, Order*, std::less<double> > AskOrders;
    
    typedef std::multimap<unsigned, pos> OrderMap;
    OrderMap m_OrderMap;
    
public:
    void match(Order& newOrder);
    void add(Order& newOrder);
    Order& remove(Order::Side side, unsigned &orderId);
    double getLastTradedPrice() { return m_LastTradedPrice; }
    long getLastTradedSize() { return m_LastTradedQuantity; }
    void printOrderBook();
    
private:
    void match(Order& newOrder, Order& bookOrder);
    
private:
    BidOrders m_bidOrders;
    AskOrders m_askOrders;
    std::string m_symbol;
    
    double m_LastTradedPrice;
    long m_LastTradedQuantity;
};
    
}

#endif
