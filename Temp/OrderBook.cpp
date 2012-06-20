//
//  OrderBook.cpp
//  ExchangeFeed
//
//  Created by Ganesh M on 20/6/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "OrderBook.h"

namespace feed {
    
OrderBook::OrderBook(const std::string &symbol)
    : m_symbol(symbol) {
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
                m_bidOrders.erase(it);
            }
            
        }
    }
}
    
    void OrderBook::match(Order &newOrder, Order &bookOrder) {
        
        if (newOrder.getSide() == bookOrder.getSide())
            return;
        
        
    }

}