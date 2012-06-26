//
//  Order.cpp
//  ExchangeFeed
//
//

#include <iostream>
#include "Order.h"

namespace feed {

Order::Order(uint64_t orderId,
             Side side,
             uint64_t quantity,
             double price)
: m_orderId(orderId)
, m_side(side)
, m_quantity(quantity)
, m_price(price)
, m_lastExecutedPrice(0.0)
, m_openQuantity(quantity)
, m_lastExecutedQuantity(0) 
, m_executedQuantity(0) {

}

Order::~Order() {
}

void Order::setQuantity(uint64_t quantity) {

    if (quantity <= m_executedQuantity) {
        m_quantity = m_executedQuantity;
        m_openQuantity = 0;
    }
    else {
        m_quantity = quantity;
        m_openQuantity = m_quantity - m_executedQuantity;
    }
}

void Order::fill(double price, uint64_t quantity)  {

    m_openQuantity -= quantity;
    m_executedQuantity += quantity;
    m_lastExecutedQuantity = quantity;
    m_lastExecutedPrice = price;
}

}
