#include <iostream>
#include "Order.hpp"

int main() {


    Order order1(0,orderSide::BUY,OrderType::Limit,50.4,10);

    order1.getPrice();

    return 0;
}

