//
//  main.cpp
//  ExchangeFeed
//
//  Created by Ganesh M on 20/6/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include "OrderBook.h"
#include "Exceptions.h"

int main (int argc, const char * argv[])
{
    feed::OrderBook orderbook("Testing");
    uint64_t count=0;

    std::ifstream infile;
    infile.open("./input.txt", std::ifstream::in);
    if (!infile.is_open()) {
        std::cerr << "Failed to open file!!" << std::endl;
        return -1;
    }
    
    std::string line;
    while (std::getline(infile, line)) {
        try {
            orderbook.processMsg(line);
        }
        catch (const feed::FeedException& e) {
            std::cerr << "Error[" << e.error_code() << "]: " << e.what() << std::endl;
        }
        if (++count%10 == 0)
            orderbook.printOrderBook(std::cout);
    }
    orderbook.printOrderBook(std::cout);
    orderbook.printSummary();

    return 0;
}
