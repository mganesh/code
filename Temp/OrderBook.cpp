//
//  OrderBook.cpp
//  ExchangeFeed
//
//  Created by Ganesh M on 20/6/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <sstream>
#include "OrderBook.h"

namespace feed {
    
OrderBook::OrderBook(const std::string &symbol)
    : m_symbol(symbol)
    , m_LastTradedQuantity(0)
    , m_LastTradedPrice(0.0) {
}

OrderBook::~OrderBook() {
    // TODO:
    // cleanup Orderbook.
}
    
void OrderBook::match(Order& newOrder) {
    
    if (newOrder.getSide() == Order::BUY) {
        while(true) {
            
            /* empty order book */
            if (m_askOrders.empty() || !newOrder.isOpen())
                return;
            
            AskOrders::iterator it = m_askOrders.begin();
            Order& bookOrder = *(it->second);
            
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
            Order& bookOrder = *(it->second);
            
            /* not matching */
            if (newOrder.getPrice() > bookOrder.getPrice())
                return;
            
            match(newOrder, bookOrder);
            if(!bookOrder.isOpen()) {
                m_LastTradedPrice = bookOrder.lastExecutedPrice();
                m_LastTradedQuantity = bookOrder.lastExecutedQuantity();
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
        m_LastTradedPrice = bookOrder.getPrice();
        m_LastTradedQuantity = std::min(newOrder.getQuantity(), bookOrder.getQuantity());
        
        newOrder.fill(m_LastTradedPrice, m_LastTradedQuantity);
        bookOrder.fill(m_LastTradedPrice, m_LastTradedQuantity);
        
    }
         
}

void OrderBook::add(Order& newOrder) {
    
    if (m_OrderMap.find(newOrder.getOrderId()) != m_OrderMap.end()) {
        std::string error("Duplicate Order id!!");
        throw InvalidOrder(error);
        //InvalidOrder Error(error);
        //throw Error;
    }
    
    // Check if any match found
    match(newOrder);
    
    // Check any open order remaining
    if (newOrder.isOpen()) {
        if (newOrder.getSide() == Order::BUY) {
            BidOrders::iterator it = m_bidOrders.insert(std::make_pair(newOrder.getPrice(), &newOrder));
            m_OrderMap.insert(std::make_pair(newOrder.getOrderId(), it));
        }
        else {
            AskOrders::iterator it = m_askOrders.insert(AskOrders::value_type(newOrder.getPrice(), &newOrder));
            m_OrderMap.insert(std::make_pair(newOrder.getOrderId(), it));
        }
    }
}

Order& OrderBook::remove(Order::Side side, unsigned &orderId) {
    
    Order* removedOrder = NULL;
    if (side == Order::BUY) {
        
        BidOrders::iterator start = m_bidOrders.begin();
        BidOrders::iterator end = m_bidOrders.end();
        for(; start != end; ++start) {
            if (start->second->getOrderId() == orderId) {
                // match found
                removedOrder = start->second;
                m_bidOrders.erase(start);
                return *removedOrder;
            }
        }
    }
    else if (side == Order::SELL) {
        
        AskOrders::iterator start = m_askOrders.begin();
        AskOrders::iterator end = m_askOrders.end();
        for(; start != end; ++start) {
            if (start->second->getOrderId() == orderId) {
                // match found
                removedOrder = start->second;
                m_askOrders.erase(start);
                return *removedOrder;
            }
        }
    }
}

void OrderBook::printOrderBook() {
    std::ostringstream oss;
    oss << "Order Book: "
        << "\n============";

    oss << "\nBuy: ";
    if (m_bidOrders.empty()) {
        oss << "Empty";
    } else {
        BidOrders::const_iterator start = m_bidOrders.begin();
        BidOrders::const_iterator end = m_bidOrders.end();
        for(; start != end; ++start) {
            oss << "\n\t" << start->second->getOpenQuantity()
                << " @ " << start->first;
        }
    }
    
    oss << "\nSell: ";
    if (m_askOrders.empty()) {
        oss << "Empty";
    } else {
        AskOrders::const_iterator start = m_askOrders.begin();
        AskOrders::const_iterator end = m_askOrders.end();
        for(; start != end; ++start) {
            oss << "\n\t" << start->second->getOpenQuantity()
            << " @ " << start->first;
        }
    }
    
    std::cout << oss.str() << std::endl;
}
    
}