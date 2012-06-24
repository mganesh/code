//
//  Exceptions.h
//  ExchangeFeed
//
//  Created by Ganesh M on 24/6/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#ifndef ExchangeFeed_Exceptions_h
#define ExchangeFeed_Exceptions_h

#include <exception>
#include <stdexcept>
#include <string>

namespace feed {

struct FeedException : public std::runtime_error {
    explicit FeedException(const std::string& error)
    : std::runtime_error(error) { }
};

struct InvalidOrder : public FeedException {
    explicit InvalidOrder(const std::string& error)
    : FeedException(error) { }
};

struct InvalidMidQuote : public FeedException {
    explicit InvalidMidQuote(const std::string& error = "NAN")
    : FeedException(error) { }
};

}

#endif
