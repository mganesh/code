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
#include "Test.h"

int main (int argc, const char * argv[])
{
    feed::OrderBook orderbook("Testing");
    std::ostringstream line;
    uint64_t count=0;

    /*
    test::Test m_Automated;
    while (m_Automated.Next(line)) {
        try {
            orderbook.processMsg(line.str());
        }
        catch (const feed::FeedException& e) {
            std::cerr << "Error[" << e.error_code() 
                      << "]: " << e.what() << " - "
                      << line.str() 
                      << std::endl;
        }

        if (++count%10 == 0) {
            orderbook.printOrderBook(std::cout);
        }
        line.str("");
    }
    
    orderbook.printOrderBook(std::cout);
    orderbook.printSummary();
    return 0;
    */
    
    std::ifstream infile;
    infile.open("./input.txt", std::ifstream::in);
    if (!infile.is_open()) {
        std::cerr << "Failed to open file!!" << std::endl;
        return -1;
    }
    

    
    std::string string_line;
    while (std::getline(infile, string_line)) {
        try {
            orderbook.processMsg(string_line);
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
