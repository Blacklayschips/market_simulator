#pragma once
#include "OrderBook.hpp"
#include <random>


class marketSim {



public:


    marketSim(OrderBook marketOrderBook,int priceOfMarket,int marketMoveUpCount,int marketMarketMoveDownCount);
    void runSimulation();






private:


    OrderBook orderBook;
    double marketPrice;
    int marketMovingUpCount;
    int marketMovingDownCount;

};


