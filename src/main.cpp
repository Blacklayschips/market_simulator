#include <iostream>
#include "Order.hpp"
#include "OrderBook.hpp"
#include "marketSim.hpp"
#include "Trader.hpp"


int main() {
    OrderBook ob;




    marketSim markSim(ob,100,0,0);
    std::vector<Trader> traders;
    //trader ID
    int i =0;
    for ( i = 0 ; i < 10 ; i++) {
        traders.emplace_back(i,typeOfTrader::Retail);
    }
    for ( i = 10 ; i < 20 ; i++) {
        traders.emplace_back(i,typeOfTrader::Momentum);
    }
    for ( i = 20 ; i < 25 ; i++) {
        traders.emplace_back(i,typeOfTrader::Whale);
    }

    markSim.addTraders(traders);



    // Print final state







    markSim.runSimulation();

    return 0;
}

