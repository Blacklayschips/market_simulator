#include <iostream>
#include "Order.hpp"
#include "OrderBook.hpp"
#include "marketSim.hpp"



int main() {
    OrderBook ob;


    Order buy1(5, orderSide::BUY, OrderType::Limit, 99.0, 2);
    ob.matchOrder(buy1);
    Order buy2(6, orderSide::BUY, OrderType::Limit, 98.5, 4);
    ob.matchOrder(buy1);


    Order marketSell(7, orderSide::SELL, OrderType::Market, 0, 10); // Price ignored
    ob.matchOrder(marketSell);

    marketSim markSim(ob,100,0,0);








    // Print final state
    ob.PrintOrderBook();

    ob.printTradeHistory();




    markSim.runSimulation();

    return 0;
}

