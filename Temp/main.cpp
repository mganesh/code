//
//  main.cpp
//  ExchangeFeed
//
//  Created by Ganesh M on 20/6/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "OrderBook.h"
#include "Exceptions.h"

int main (int argc, const char * argv[])
{

    feed::OrderBook orderbook("Testing");
    feed::Order order(1, feed::Order::BUY, 10, 100);
    feed::Order o1(2, feed::Order::BUY, 20, 102);
    feed::Order o2(3, feed::Order::BUY, 15, 101);

    feed::Order s1(4, feed::Order::SELL, 21, 102);
    orderbook.add(o2);
    orderbook.add(order);
    try {
        orderbook.add(o1);
    } catch (feed::FeedException& e) {
        std::cerr << e.what() << std::endl;
    }
    
    orderbook.add(s1);
    orderbook.printOrderBook();
    
    return 0;
}

