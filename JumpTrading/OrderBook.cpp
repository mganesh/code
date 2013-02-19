//
//  OrderBook.cpp
//  ExchangeFeed
//
//  Created by Ganesh M on 24/6/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include <stdlib.h>
#include <errno.h>
#include <iostream>
#include <sstream>
#include <iterator>
#include <limits>
#include <vector>
#include <assert.h>
#include "OrderBook.h"

namespace {
    inline bool is_nagative(char c, char symbol='-') {
        return (c == symbol);
    }

    inline bool isUint(const std::string& s) {
        return s.find_first_not_of("0123456789") == std::string::npos;
    }

    inline bool isUdouble(const std::string& s) {
        return s.find_first_not_of("0123456789.") == std::string::npos;
    }
}
namespace feed {

bool isAlmostSame(double a, double b) {
    static const double epsilon = std::numeric_limits<double>::epsilon();
    return fabs(a-b) < epsilon;
}

void split(const std::string& s, char delim, std::vector<std::string> &result) {
    std::stringstream ss(s);
    std::string token;
    while (std::getline(ss, token, delim)) {
        result.push_back(token);
    }
}

OrderBook::OrderBook(const std::string &symbol)
    : m_symbol(symbol)
    , m_LastTradedQuantity(0)
    , m_LastTradedPrice(0.0)
    , m_TotalMsgProcessed(0)
    , m_TotalValidMsg(0)
    , m_TotalInvalidMsg(0)
    , m_TotalFilledOrders(0)
    , m_low(std::numeric_limits<double>::max())
    , m_high(-m_low) 
	, m_TotalModified(0)
    , m_TotalRemoved(0)

{

}

OrderBook::~OrderBook() {

    {
        BidOrders::iterator start = m_bidOrders.begin();
        BidOrders::iterator end = m_bidOrders.end();
        m_bidOrders.erase(start, end);
        m_bidOrders.clear();
    }
    {
        AskOrders::iterator start = m_askOrders.begin();
        AskOrders::iterator end = m_askOrders.end();
        m_askOrders.erase(start, end);
        m_askOrders.clear();
    }
    {
        OrderMap::iterator start = m_OrderMap.begin();
        OrderMap::iterator end = m_OrderMap.end();
        for(; start != end; ++start) {
            Order* order = start->second;
            delete order;
        }
        m_OrderMap.erase(start, end);
        m_OrderMap.clear();
    }

}

void OrderBook::processMsg(const std::string& msg) {

    try {

        if (msg.empty())
         return;

    ++m_TotalMsgProcessed;

    typedef std::vector<std::string> Tokens;
    Tokens tokens;
    split(msg, ',', tokens);

    //Validate input
    if (tokens.size() != 5) {
        std::ostringstream oss;
        oss << "Invalid Msg (" << msg << ")";
        throw InvalidOrder(Exception::INVALID_INPUT, oss.str());
    }

    uint64_t order_id = getOrderId(tokens[1]);
    Order::Side side = getSide(tokens[2]);
    uint64_t quantity = getSize(tokens[3]);
    double price = getPrice(tokens[4]);

    if (tokens[0] == "A") {
        if (m_OrderMap.find(order_id) != m_OrderMap.end()) {
            // duplicate order id;
            std::ostringstream oss;
            oss << "Duplicate Order id: " << order_id;
            throw InvalidOrder(Exception::DUPLICATE_ORDER_ID, oss.str());
        }

        Order* order = new Order(order_id, side,
                                 quantity, price);
        bool added = add(*order);
        if (!added)
            delete order;
    }
    else if (tokens[0] == "X") {
        // get order & check price & quantity matches
        Order* o = remove(side, quantity, price, order_id);
        delete o;
		++m_TotalRemoved;
    }
    else if (tokens[0] == "M") {
        OrderMap::iterator pos = m_OrderMap.find(order_id);
        if (pos == m_OrderMap.end()) {
            //  order id not found
            std::ostringstream oss;
            oss << "Order id: " << order_id
                << ", Not Found!!";
            throw InvalidOrder(Exception::INVALID_ORDER_ID_MODIFY, oss.str());
        }

        Order* original = pos->second;
        if (original->getSide() != side) {
            std::ostringstream oss;
            oss << "Modify request, side mismatch in order request: " << order_id;
            throw InvalidOrder(Exception::INVALID_REQUEST_MODIFY, oss.str());
        }
        
        if (original->getExecutedQty() >= quantity) {
            std::ostringstream oss;
            oss << "Modify request, invalid quantity: " << order_id;
            throw InvalidOrder(Exception::INVALID_REQUEST_MODIFY, oss.str());
        }
        
        remove(original->getSide(), original->getQuantity(), original->getPrice(), original->getOrderId());

        original->setPrice(price);
        original->setQuantity(quantity);
<<<<<<< HEAD
        
        bool added = add(*original);
        if (!added)
            delete original;
        
=======

		if (side == Order::SELL)
			sell_orderbook();
		else
			buy_orderbook();

>>>>>>> Sync
		++m_TotalModified;
    }
    else {
        // invalid action
        std::ostringstream oss;
        oss << "Invalid Action: " << msg;
        throw InvalidOrder(Exception::INVALID_ACTION, oss.str());
    }
    ++m_TotalValidMsg;
 } catch (const FeedException& e) {
     ++m_TotalInvalidMsg;
       illegalMsg[e.error_code()] += 1;
       throw e;
   }

    try {

        std::cout << midQuotes() << std::endl;
    }
    catch(const InvalidMidQuote& e) {
        std::cout << e.what() << std::endl;
    }
}

void OrderBook::match(Order& newOrder) {

    if (newOrder.getSide() == Order::BUY) {
        while(true) {

            /* empty order book */
            if (m_askOrders.empty() || !newOrder.isOpen())
                return;

            AskOrders::iterator it = m_askOrders.begin();
            Order& bookOrder = *(it->second->second);

            /* not matching */
            if (newOrder.getPrice() < bookOrder.getPrice())
                return;
            match(newOrder, bookOrder);
            if(!bookOrder.isOpen()) {
                m_askOrders.erase(it);
            }

        }
    }
    else {
        while(true) {

            /* empty order book */
            if (m_bidOrders.empty() || !newOrder.isOpen())
                return;

            BidOrders::iterator it = m_bidOrders.begin();
            Order& bookOrder = *(it->second->second);

            /* not matching */
            if (newOrder.getPrice() > bookOrder.getPrice())
                return;

            match(newOrder, bookOrder);
            if(!bookOrder.isOpen()) {
                m_bidOrders.erase(it);
            }

        }
    }
}

void OrderBook::match(Order &newOrder, Order &bookOrder) {


    if (newOrder.getSide() == bookOrder.getSide())
        return;

    if (
        (newOrder.getSide() == Order::BUY
         && newOrder.getPrice() >= bookOrder.getPrice())

        || (newOrder.getSide() == Order::SELL
            && newOrder.getPrice() <= bookOrder.getPrice())
        )
    {

        double price = bookOrder.getPrice();
        uint64_t quantity = std::min(newOrder.getOpenQuantity(), bookOrder.getOpenQuantity());

        newOrder.fill(price, quantity);
        bookOrder.fill(price, quantity);

        /* Trade Stats */
        if (price >m_high)
            m_high = price;

        if (price < m_low)
            m_low = price;

        m_TotalFilledOrders += quantity;

        if (isAlmostSame(m_LastTradedPrice, price)) {
            m_LastTradedQuantity += quantity;
        }
        else {
            m_LastTradedQuantity = quantity;
        }

        assert(newOrder.lastExecutedQuantity() == quantity);
        assert(isAlmostSame(newOrder.lastExecutedPrice(), price));

        m_LastTradedPrice = price;
        printTradeStats();
    }

}

bool OrderBook::add(Order& newOrder) {

    if (m_OrderMap.find(newOrder.getOrderId()) != m_OrderMap.end()) {
        std::ostringstream oss;
        oss << "Duplicate order id:" << newOrder.getOrderId();

        throw InvalidOrder(Exception::DUPLICATE_ORDER_ID, oss.str());
    }

<<<<<<< HEAD
    OrderMap::iterator it = m_OrderMap.insert(std::make_pair(newOrder.getOrderId(), &newOrder)).first;
=======
	uint64_t filled = m_TotalFilledOrders;
    OrderMap::iterator it = m_OrderMap.insert(std::make_pair(newOrder.getOrderId(), &newOrder));
>>>>>>> Sync
    // Check if any match found
    match(newOrder);

    // Check any open order remaining
    if (newOrder.isOpen()) {
		double price = newOrder.getPrice();

		/* Standard does not comfirm the elements with equal_range
		   will be stable. Provide hints (lower_bound & upper_bound)
		   while inserting elements into the map
		*/

        if (newOrder.getSide() == Order::BUY) {
            m_bidOrders.insert(m_bidOrders.lower_bound(price), BidOrders::value_type(price, it));
			buy_orderbook();
        }
        else {
            m_askOrders.insert(m_askOrders.upper_bound(price), AskOrders::value_type(price, it));
			sell_orderbook();
        }
        return true;
    }

<<<<<<< HEAD
    // Order is completely filled. clean it up
    m_OrderMap.erase(it);
    return false;
=======
	if (filled != m_TotalFilledOrders) {
		if (newOrder.getSide() == Order::BUY) {
			sell_orderbook();
		}
		else
			buy_orderbook();
	}
>>>>>>> Sync
}

Order* OrderBook::remove(Order::Side side
                       , uint64_t quantity
                       , double price
                       , uint64_t orderId) {

    // Order id valid ?
    OrderMap::iterator pos = m_OrderMap.find(orderId);
    /* order not found or order completely filled */
    if (pos == m_OrderMap.end() ||
            !pos->second->isOpen()) {
        std::ostringstream oss;
        oss << "Invalid Order id: " << orderId;
        throw InvalidOrder(Exception::INVALID_ORDER_ID_REMOVE, oss.str());
    }

    Order* OriginalOrder = pos->second;
    assert (OriginalOrder != NULL);

    if ( side != OriginalOrder->getSide()
        || quantity != OriginalOrder->getQuantity()
        || !isAlmostSame(price, OriginalOrder->getPrice())) {

        // Order information not matching
        std::ostringstream oss;
        oss << "Remove Order request not matching " << orderId;
        throw InvalidOrder(Exception::INVALID_REQUEST_REMOVE, oss.str());
    }

    if (side == Order::BUY) {

        BidOrders::iterator start = m_bidOrders.begin();
        BidOrders::iterator end = m_bidOrders.end();
        for(; start != end; ++start) {
            if (start->second->second->getOrderId() == orderId) {
                // match found
                m_bidOrders.erase(start);
<<<<<<< HEAD
=======
				buy_orderbook();
                return;
>>>>>>> Sync
            }
        }
    }
    else if (side == Order::SELL) {

        AskOrders::iterator start = m_askOrders.begin();
        AskOrders::iterator end = m_askOrders.end();
        for(; start != end; ++start) {
            if (start->second->second->getOrderId() == orderId) {
                // match found
                m_askOrders.erase(start);
<<<<<<< HEAD
=======
				sell_orderbook();
                return;
>>>>>>> Sync
            }
        }
    }
    
    m_OrderMap.erase(pos);
    return OriginalOrder;

}

void OrderBook::buy_orderbook() {
	buy_ob.clear();
	buy_ob.seekp(0); // for outputs

	buy_ob << "\nBuy: ";
	if (m_bidOrders.empty()) {
		buy_ob << "\n\tEmpty"; 
	}
	else {
        BidOrders::const_iterator start = m_bidOrders.begin();
        BidOrders::const_iterator end = m_bidOrders.end();
        for(; start != end; ++start) {
            buy_ob << "\n\t"
                << start->second->second->getOpenQuantity()
                << "@" << start->first;
        }
	}

	buy_ob << std::ends;
}

void OrderBook::sell_orderbook() {
	sell_ob.clear();
	sell_ob.seekp(0); // for outputs

	sell_ob << "\nSell: ";
	if (m_askOrders.empty()) {
		sell_ob << "\n\tEmpty"; 
	}
	else {
        AskOrders::const_iterator start = m_askOrders.begin();
        AskOrders::const_iterator end = m_askOrders.end();
        for(; start != end; ++start) {
            sell_ob << "\n\t"
                << start->second->second->getOpenQuantity()
                << "@" << start->first;
        }
	}

	sell_ob << std::ends;
}

void OrderBook::printOrderBook2(std::ostream& os) {
	os << buy_ob.str();
	os << sell_ob.str();
	os << std::endl;
	return;
}

void OrderBook::printOrderBook(std::ostream& os) {
	std::ostringstream oss;
	//oss.sync_with_stdio(false);
    oss << "\nOrder Book: "
        << "\n============";

    oss << "\nBuy: ";
    if (m_bidOrders.empty()) {
        oss << "\n\tEmpty";
    } else {
        BidOrders::const_iterator start = m_bidOrders.begin();
        BidOrders::const_iterator end = m_bidOrders.end();
        for(; start != end; ++start) {
            oss << "\n\t"
<<<<<<< HEAD
                //<< start->second->second->getOrderId() << "|"
=======
>>>>>>> Sync
                << start->second->second->getOpenQuantity()
                << "@" << start->first;
        }
    }

    oss << "\nSell: ";
    if (m_askOrders.empty()) {
        oss << "\n\tEmpty";
    } else {
        AskOrders::const_iterator start = m_askOrders.begin();
        AskOrders::const_iterator end = m_askOrders.end();
        for(; start != end; ++start) {
            oss << "\n\t"
<<<<<<< HEAD
                //<< start->second->second->getOrderId() << "|"
=======
>>>>>>> Sync
                << start->second->second->getOpenQuantity()
            << "@" << start->first;
        }
    }
<<<<<<< HEAD
    oss << std::endl;
=======

	os << oss.str() << std::endl;
>>>>>>> Sync
}

void OrderBook::printTradeStats() {

    std::ostringstream oss;
    oss << "T," << m_LastTradedQuantity
        << "," << m_LastTradedPrice;
    std::cout << oss.str() << std::endl;
}

double OrderBook::midQuotes() {
    if (m_bidOrders.empty() || m_askOrders.empty())
        throw InvalidMidQuote();
    double bestbid = m_bidOrders.begin()->first;
    double bestask = m_askOrders.begin()->first;
    return(bestbid+bestask)/2;

}

Order::Side OrderBook::getSide(const std::string &side)
{
    if (side == "B")
        return Order::BUY;
    else if (side == "S")
        return Order::SELL;
    throw InvalidOrder(Exception::INVALID_SIDE, "Invalid Side");
}

double OrderBook::getPrice(const std::string &price) {

    static const double max = std::numeric_limits<double>::max();
    double value = ::atof(price.c_str());
    if (!isUdouble(price) || errno != 0 || value<=0 || value >= max) {
        std::ostringstream oss;
        oss << "Illegal Price: " << price;
        throw InvalidOrder(Exception::INVALID_PRICE, oss.str());
    }
    return value;
}

uint64_t OrderBook::getSize(const std::string &size) {
    errno = 0;
    char* end = NULL;
    static const long int max = std::numeric_limits<long int>::max();
    uint64_t value = strtol(size.c_str(), &end, 10);
    if (!isUint(size) || errno != 0 || value >= (uint64_t)max) {
        std::ostringstream oss;
        oss << "Illegal Quantity: " << size;
        throw InvalidOrder(Exception::INVALID_QUANTITY, oss.str());
    }
    return value;
}

uint64_t OrderBook::getOrderId(const std::string &orderid) {
    // Check for any errors
    char* end;
    errno = 0;
    static const long int max = std::numeric_limits<long int>::max();
    uint64_t value = strtoul(orderid.c_str(), &end, 10);
    if ( !isUint(orderid) || errno != 0 || value >= (uint64_t)max)
    {
        std::ostringstream oss;
        oss << "Illegal order id: " << orderid;
        throw InvalidOrder(Exception::ILLEGAL_ORDER_ID, oss.str());
    }

    return value;

}

<<<<<<< HEAD
void OrderBook::printSummary(std::ostream& oss) {
//    std::ostringstream oss;
=======
void OrderBook::printSummary(std::ostream& os) {
    std::ostringstream oss;
>>>>>>> Sync

    if (m_TotalFilledOrders == 0)
    {
        m_high = 0;
        m_low = 0;
    }

    oss << "\nOrder Book Summary:"
        << "\n-------------------"
        << "\nTotal Msg received    : " << m_TotalMsgProcessed
        << "\nTotal Valid Msg       : " << m_TotalValidMsg
        << "\nTotal Invalid Msg     : " << m_TotalInvalidMsg
        << "\nTotal Quantity Filled : " << m_TotalFilledOrders
		<< "\nTotal Orders removed  : " << m_TotalRemoved
		<< "\nTotal Orders modified : " << m_TotalModified
        << "\nHigh Price            : " << m_high
        << "\nLow Price             : " << m_low
        ;

    IllegalMsg::iterator start = illegalMsg.begin();
    IllegalMsg::iterator end = illegalMsg.end();
    oss << "\nError Summary:";
    oss << "\n~~~~~~~~~~~~~~~";
    for(; start!= end; ++start) {
        uint16_t index = start->first;
        oss << "\n" << Exception::ErrorString[index] 
            << " : " << start->second;
    }
        
<<<<<<< HEAD
    oss << std::endl;
=======
    os << oss.str() << std::endl;
>>>>>>> Sync
}

}
