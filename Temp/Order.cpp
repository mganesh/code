//
//  Order.cpp
//  ExchangeFeed
//
//  Created by Ganesh M on 21/6/12.
//

#include <iostream>
#include "Order.h"

namespace feed {

Order::Order(unsigned orderId,
             Side side,
             long quantity,
             double price)
: m_orderId(orderId)
, m_side(side)
, m_quantity(quantity)
, m_price(price)
, m_openQuantity(quantity)
, m_executedQuantity(0)
, m_lastExecutedPrice(0.0)
, m_lastExecutedQuantity(0) {
    
}

Order::~Order() { }

void Order::setQuantity(long quantity) {
    
    if (quantity <= m_executedQuantity) {
        m_quantity = m_executedQuantity;
        m_openQuantity = 0;
    }
    else {
        m_quantity = quantity;
        m_openQuantity = m_quantity - m_executedQuantity;
    }
}
 
void Order::fill(double price, long quantity)  {
    
    m_openQuantity -= quantity;
    m_executedQuantity += quantity;
    m_lastExecutedQuantity = quantity;
    m_lastExecutedPrice = price;
}
    
}