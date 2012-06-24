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
#include <vector>
#include <math.h>

#include "Order.h"
#include "Exceptions.h"


namespace feed {
    bool isAlmostSame(double, double);
    void split(const std::string& s, char delim, std::vector<std::string> &result);
    
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
    void processMsg(const std::string& order_msg);
    void match(Order& newOrder);
    void add(Order& newOrder);
    void remove(Order::Side side, long quantity, double price, unsigned &orderId);
    double getLastTradedPrice() { return m_LastTradedPrice; }
    long getLastTradedSize() { return m_LastTradedQuantity; }
    void printOrderBook();
    double midQuotes();
    void printTradeStats();
    
private:
    void match(Order& newOrder, Order& bookOrder);
    Order::Side getSide(const std::string& side);
    double getPrice(const std::string& price);
    long getSize(const std::string& size);
private:
    BidOrders m_bidOrders;
    AskOrders m_askOrders;
    std::string m_symbol;
    
    double m_LastTradedPrice;
    long m_LastTradedQuantity;
};
    
}

#endif
