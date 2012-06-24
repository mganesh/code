//
//  OrderBook.cpp
//  ExchangeFeed
//
//  Created by Ganesh M on 20/6/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <iterator>
#include <limits>
#include <vector>
#include <assert.h>
#include "OrderBook.h"

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
    , m_LastTradedPrice(0.0) {
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

    if (msg.empty()) return;
    
    typedef std::vector<std::string> Tokens;
    Tokens tokens;
    split(msg, ',', tokens);
    
    //Validate input
    if (tokens.size() != 5) {
        std::ostringstream oss;
        oss << "Invalid Msg (" << msg << ")";
        throw InvalidOrder(Exception::INVALID_INPUT, oss.str());
    }
    
    unsigned order_id = ::atoi(tokens[1].c_str());
    Order::Side side = getSide(tokens[2]);
    long quantity = getSize(tokens[3]);
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
        add(*order);
    }
    else if (tokens[0] == "X") {
        // get order & check price & quantity matches
        remove(side, quantity, price, order_id);
    }
    else if (tokens[0] == "M") {
        OrderMap::iterator pos = m_OrderMap.find(order_id);
        if (pos == m_OrderMap.end()) {
            // duplicate order id;
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
        
        original->setPrice(price);
        original->setQuantity(quantity);
            
    }
 }
	catch (const FeedException& e) {
		illegalMsg[e.error_code()] += 1;
		throw e;
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
				//remove_from_orderbook(it->second->getOrderId());
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
				//remove_from_orderbook(it->second->getOrderId());
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
        long quantity = std::min(newOrder.getOpenQuantity(), bookOrder.getOpenQuantity());
        
        
        newOrder.fill(price, quantity);
        bookOrder.fill(price, quantity);
        
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

void OrderBook::add(Order& newOrder) {
    
    if (m_OrderMap.find(newOrder.getOrderId()) != m_OrderMap.end()) {
		std::ostringstream oss;
		oss << "Duplicate order id:" << newOrder.getOrderId();

		throw InvalidOrder(Exception::DUPLICATE_ORDER_ID, oss.str());
    }
    
	OrderMap::iterator it = m_OrderMap.insert(std::make_pair(newOrder.getOrderId(), &newOrder));
    // Check if any match found
    match(newOrder);
    
    // Check any open order remaining
    if (newOrder.isOpen()) {
        if (newOrder.getSide() == Order::BUY) {
            m_bidOrders.insert(std::make_pair(newOrder.getPrice(), it));
        }
        else {
            m_askOrders.insert(AskOrders::value_type(newOrder.getPrice(), it));
        }
    }
}

void OrderBook::remove(Order::Side side
                       , long quantity
                       , double price
                       , unsigned &orderId) {
    
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
    if (!OriginalOrder) return;
    
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
                return;
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
                return;
            }
        }
    }
}

void OrderBook::printOrderBook() {
    std::ostringstream oss;
    oss << "\nOrder Book: "
        << "\n============";

    oss << "\nBuy: ";
    if (m_bidOrders.empty()) {
        oss << "Empty";
    } else {
        BidOrders::const_iterator start = m_bidOrders.begin();
        BidOrders::const_iterator end = m_bidOrders.end();
        for(; start != end; ++start) {
            oss << "\n\t" 
				<< start->second->second->getOrderId() << "|"
				<< start->second->second->getOpenQuantity()
                << "@" << start->first;
        }
    }
    
    oss << "\nSell: ";
    if (m_askOrders.empty()) {
        oss << "Empty";
    } else {
        AskOrders::const_iterator start = m_askOrders.begin();
        AskOrders::const_iterator end = m_askOrders.end();
        for(; start != end; ++start) {
            oss << "\n\t" 
				<< start->second->second->getOrderId() << "|"
				<< start->second->second->getOpenQuantity()
            << " @ " << start->first;
        }
    }
    
    std::cout << oss.str() << std::endl;
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
    double result = ::atof(price.c_str());
    if (result > 0.0)
        return result;
    std::ostringstream oss;
    oss << "Illegal Price: " << price;
    throw InvalidOrder(Exception::INVALID_PRICE, oss.str());
}

long OrderBook::getSize(const std::string &size) {
    long result = ::atol(size.c_str());
    if (result > 0)
        return result;
    std::ostringstream oss;
    oss << "Illegal Quantity: " << size;
    throw InvalidOrder(Exception::INVALID_QUANTITY, oss.str());
}

}
