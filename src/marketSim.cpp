#include "marketSim.hpp"
#include "Order.hpp"
#include <thread>
#include <iostream>
#include <chrono>



double marketSim::getPriceOfMarket()const {

    return marketPrice;

}

void marketSim::addTraders(const std::vector<Trader>& listOfTraders) {

    traders = listOfTraders;

}

marketSim::marketSim(OrderBook marketsOrderBook,int marketPrice,int marketDirectionCountUp,int marketDirectionCountDown):
            orderBook(marketsOrderBook),marketPrice(marketPrice),marketMovingUpCount(marketDirectionCountUp),marketMovingDownCount(marketDirectionCountDown)
{}


void marketSim::runSimulation() {

    using namespace std::chrono;
    using namespace std::literals::chrono_literals;

    auto ticktime = 100ms;
    bool isMarketRunning = true;

    std::cout<<"Current market price is  "<<marketPrice<<'\n';
    while (isMarketRunning) {


        double marketPriceBefore = marketPrice;
        auto start = high_resolution_clock::now();

        std::cout << "Perform orderbook things\n";

        for (Trader& trader : traders) {

            auto maybeOrder = trader.generateOrder(trader.getTraderID(),marketPrice,marketMovingDownCount,marketMovingUpCount);
            if (maybeOrder) {
                std::cout<<"Current market price is  "<<marketPrice<<'\n';
                std::cout<<"Price of order being added is"<<maybeOrder->getPrice()<<'\n';
                std::cout<<"Quantity of the order being added/matched is "<< maybeOrder->getQuantity()<<'\n';
                if (maybeOrder->getSide()==orderSide::BUY) {
                    std::cout<<"Type of order is a buy order"<<'\n';
                }else {
                    std::cout<<"Type of order is a sell order"<<'\n';
                }

                orderBook.matchOrder(*maybeOrder,marketPrice);
            }

        }


        orderBook.PrintOrderBook();

        auto end = high_resolution_clock::now();
        auto duration = end - start;


        double marketPriceAfter = marketPrice;

        if (marketPriceAfter>marketPriceBefore) {

            marketMovingUpCount++;
        } else if (marketPriceBefore>marketPriceAfter) {
            marketMovingDownCount++;
        }

        if (marketMovingUpCount==5) {
            marketMovingUpCount=0;
        }else if (marketMovingDownCount==5) {
            marketMovingDownCount=0;
        }

        if (duration < ticktime) {
            std::this_thread::sleep_for(ticktime - duration);
        }




    }




}