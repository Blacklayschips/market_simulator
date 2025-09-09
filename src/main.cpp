#include <iostream>
#include "Order.hpp"
#include "OrderBook.hpp"
#include "marketSim.hpp"
#include "Trader.hpp"


int main() {
    std::remove("candles.csv");
    OrderBook ob;




    marketSim markSim(ob,100,0,0);
    std::vector<Trader> traders;
    //trader ID
    int i =0;
    for ( i = 0 ; i < 3000 ; i++) {
        traders.emplace_back(i,typeOfTrader::Retail);
    }
    for ( i =3000 ; i < 3750 ; i++) {
        traders.emplace_back(i,typeOfTrader::Momentum);
    }
    for ( i = 3750 ; i < 4000 ; i++) {
        traders.emplace_back(i,typeOfTrader::Whale);
    }

    markSim.addTraders(traders);



    // Print final state







    markSim.runSimulation();

    return 0;
}

//