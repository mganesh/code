//
//  main.cpp
//  ExchangeFeed
//
//  Created by Ganesh M on 20/6/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "OrderBook.h"
#include "Exceptions.h"

int main (int argc, const char * argv[])
{

    feed::OrderBook orderbook("Testing");
    std::string line;

    std::ifstream infile;
    infile.open("/Users/mganesh/Documents/ExchangeFeed/ExchangeFeed/input.txt", std::ifstream::in);
    if (!infile.is_open()) {
        std::cerr << "Failed to open file!!" << std::endl;
    }
    
    while (std::getline(infile, line)) {
        //std::cout << line << std::endl;
        try {
            orderbook.processMsg(line);
        }
        catch (const feed::FeedException& e) {
            std::cerr << e.what() << std::endl;
        }
    }
    
    std::cout << "The End !! " << std::endl;
    return 0;
}

