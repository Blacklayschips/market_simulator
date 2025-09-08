#pragma once
#include "OrderBook.hpp"
#include <random>
#include "Trader.hpp"

class marketSim {



public:


    marketSim(OrderBook marketOrderBook,int priceOfMarket,int marketMoveUpCount,int marketMarketMoveDownCount);
    void runSimulation();
    double getPriceOfMarket() const;
    void addTraders(const std::vector<Trader>& listOfTraders);
    OrderBook orderBook;


private:



    std::vector<Trader> traders;
    double marketPrice;
    int marketMovingUpCount;
    int marketMovingDownCount;

};


//