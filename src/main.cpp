#include <iostream>
#include "Order.hpp"
#include "OrderBook.hpp"

int main() {
    OrderBook orderBook;
    Order orderOG(0,orderSide::SELL,OrderType::Market,50.3,5);
    Order order1(1,orderSide::BUY,OrderType::Limit,50.4,10);

    orderBook.matchOrder(orderOG);
    orderBook.matchOrder(order1);
    std::cout<<order1.getQuantity() <<'\n';
    return 0;
}

