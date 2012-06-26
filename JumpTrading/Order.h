//
//  Order.h
//  ExchangeFeed
//
//

#ifndef ExchangeFeed_Order_h
#define ExchangeFeed_Order_h

#include <stdint.h>
#include <string>

namespace feed {

class Order {
public:

    enum Side {
        BUY = 1,
        SELL = 2
    };

    Order(uint64_t orderId,
          Side side,
          uint64_t quantity,
          double price);
    ~Order();

    uint64_t getOrderId() { return m_orderId;}
    Side getSide() const { return m_side; }
    double getPrice() const { return m_price; }
    uint64_t getQuantity() const { return m_quantity; }

    bool isOpen() { return m_openQuantity > 0; }

    void setPrice(double price) { m_price = price; }
    void setQuantity(uint64_t quantity);
    void setOpenQuantity(uint64_t openQuantity) { m_openQuantity = openQuantity; }

    void fill(double price, uint64_t quantity);

    double lastExecutedPrice() { return m_lastExecutedPrice; }
    uint64_t lastExecutedQuantity() { return m_lastExecutedQuantity; }
    uint64_t getOpenQuantity() { return m_openQuantity; }
private:

    uint64_t m_orderId;
    Side m_side;

    uint64_t m_quantity;
    double m_price;
    double m_lastExecutedPrice;

    uint64_t m_openQuantity;
    uint64_t m_lastExecutedQuantity;
    uint64_t m_executedQuantity;

};
}

#endif

