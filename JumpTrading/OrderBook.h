//
//  OrderBook.h
//  ExchangeFeed
//
//  Created by Ganesh M on 24/6/12.
//

#ifndef ExchangeFeed_OrderBook_h
#define ExchangeFeed_OrderBook_h

#include <map>
#include <string>
#include <vector>
#include <set>
#include <math.h>
#include <stdint.h>
#include <limits>

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

    typedef std::multimap<uint64_t, Order*> OrderMap;
    typedef OrderMap::iterator pos;

    typedef std::multimap<double, pos, std::greater<double> > BidOrders;
    typedef std::multimap<double, pos, std::less<double> > AskOrders;
    typedef std::map<Exception::Errors, uint64_t> IllegalMsg;



public:
    void processMsg(const std::string& order_msg);
    void printOrderBook(std::ostream&);
    void printSummary();

private:
    void match(Order& newOrder, Order& bookOrder);
    uint64_t getOrderId(const std::string& orderid);
    Order::Side getSide(const std::string& side);
    double getPrice(const std::string& price);
    uint64_t getSize(const std::string& size);
    void match(Order& newOrder);
    void add(Order& newOrder);
    void remove(Order::Side side, uint64_t quantity, double price, uint64_t &orderId);
    double getLastTradedPrice() { return m_LastTradedPrice; }
    uint64_t getLastTradedSize() { return m_LastTradedQuantity; }
    double midQuotes();
    void printTradeStats();

private:
    BidOrders m_bidOrders;
    AskOrders m_askOrders;

    std::string m_symbol;
    uint64_t m_LastTradedQuantity;
    double m_LastTradedPrice;
    uint64_t m_TotalMsgProcessed;
    uint64_t m_TotalValidMsg;
    uint64_t m_TotalInvalidMsg;
    uint64_t m_TotalFilledOrders;
    double   m_low;
    double   m_high;
	uint64_t m_TotalModified;
	uint64_t m_TotalRemoved;

    OrderMap m_OrderMap;
    IllegalMsg illegalMsg;
};

}

#endif

