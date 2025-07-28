#include <iostream>
#include "Order.hpp"

int main() {


    Order order1(0,orderSide::BUY,OrderType::Limit,50.4,10);

    std::cout<<order1.getPrice() <<'\n';
    std::cout<<order1.getTimestamp() <<'\n';
    return 0;
}

