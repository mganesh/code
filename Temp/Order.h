//
//  Order.h
//  ExchangeFeed
//
//  Created by Ganesh M on 20/6/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#ifndef ExchangeFeed_Order_h
#define ExchangeFeed_Order_h

#include <string>

namespace feed {
    
class Order {
public:
    
    enum Side {
        BUY = 1,
        SELL = 2
    };
    
    Order(const std::string &orderId,
          Side side,
          long quantity,
          double price);
    ~Order();
    
    const std::string &getOrderId() const { return m_orderId;}
    Side getSide() const { return m_side; }
    double getPrice() const { return m_price; }
    long getQuantity() const { return m_quantity;}
    bool isOpen() { return m_openQuantity > 0; }
    
    void setPrice(double price) { m_price = price; }
    void setQuantity(long quantity);
    void setOpenQuantity(long openQuantity) { m_openQuantity = openQuantity; }
    
    void fill(double price, long quantity);
    
private:
    
    std::string m_orderId;
    Side m_side;
    
    double m_price;
    double m_lastExecutedPrice;
    
    long m_quantity;
    long m_openQuantity;
    long m_executedQuantity;
    long m_lastExecutedQuantity;
    
};
}

#endif
