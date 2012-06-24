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

namespace Exception {
	enum Errors {
		UNKNOWN = 0,
		INVALID_INPUT = 1,
		DUPLICATE_ORDER_ID,
		INVALID_ORDER_ID_MODIFY,
		INVALID_REQUEST_MODIFY,
		INVALID_ORDER_ID_REMOVE,
		INVALID_REQUEST_REMOVE,
		INVALID_PRICE,
		INVALID_QUANTITY,
		INVALID_SIDE,
		INVALID_MIDQUOTES
	};
}


struct FeedException : public std::runtime_error {
    explicit FeedException(Exception::Errors code, const std::string& error)
    : std::runtime_error(error)
	, m_error_code(code) { }

	Exception::Errors error_code() const
	{
		return m_error_code;
	}
private:
	Exception::Errors m_error_code;
};

struct InvalidOrder : public FeedException {
    InvalidOrder(Exception::Errors code, const std::string& error)
    : FeedException(code, error)
	, m_error_code(code){ }

	Exception::Errors error_code() const
	{
		return m_error_code;
	}
private:
	Exception::Errors m_error_code;
};

struct InvalidMidQuote : public FeedException {
    explicit InvalidMidQuote(const std::string& error = "NAN")
    : FeedException(Exception::UNKNOWN, error) { }
};

}

#endif
