#include "Trader.hpp"
//
#include <iostream>
#include "Order.hpp"
#include <random>
#include <optional>

int Trader::getTraderID()const {

    return traderID;

}
typeOfTrader Trader::getType()const {
    return traderType;
}
std::optional<Order> Trader::generateOrder(int orderID,double curentMarketPrice,int marketDirectionCountUp,int marketDirectionCountDown) {


    std::random_device rd;
    std::mt19937 gen(rd());

    orderSide BuyOrSellSide;
    OrderType typeOfOrder;

    std::uniform_int_distribution<int> distribution(0, 1);
    if (distribution(gen) != 0) {
        typeOfOrder =OrderType::Limit;
    }else {
        typeOfOrder = OrderType::Market;
    }



    BuyOrSellSide = orderSide::BUY;

    if (traderType==typeOfTrader::Retail) {
        std::uniform_int_distribution<int> distribution(0, 3);
        if (distribution(gen) != 0) return std::nullopt;
        std::uniform_int_distribution<int> distribution2(0, 1);
        if (distribution2(gen) != 0) {
            BuyOrSellSide = orderSide::BUY;
        }else {
            BuyOrSellSide = orderSide::SELL;
        }
    }else if (traderType==typeOfTrader::Whale) {
        std::uniform_int_distribution<int> distribution(0, 5);
        if (distribution(gen) != 0) return std::nullopt;
        std::uniform_int_distribution<int> distribution2(0, 1);
        if (distribution2(gen) != 0) {
            BuyOrSellSide = orderSide::BUY;
        }else {
            BuyOrSellSide = orderSide::SELL;
        }
    }else {

        if (marketDirectionCountUp>=10) {
            BuyOrSellSide = orderSide::BUY;
        } else if (marketDirectionCountUp>=8) {
            std::uniform_int_distribution<int> distribution(0, 1);
            if (distribution(gen) == 0) return std::nullopt;
            BuyOrSellSide = orderSide::BUY;
        }  else if (marketDirectionCountUp>=5) {
            std::uniform_int_distribution<int> distribution(0, 3);
            if (distribution(gen) != 0) return std::nullopt;
            BuyOrSellSide = orderSide::BUY;
        }else if (marketDirectionCountDown>=10) {
            BuyOrSellSide = orderSide::SELL;
        } else if (marketDirectionCountDown>=8) {
            std::uniform_int_distribution<int> distribution(0, 1);
            if (distribution(gen) == 0) return std::nullopt;
            BuyOrSellSide = orderSide::SELL;
        }  else if (marketDirectionCountDown>=5) {
            std::uniform_int_distribution<int> distribution(0, 3);
            if (distribution(gen) != 0) return std::nullopt;
            BuyOrSellSide = orderSide::SELL;
        }

    }




    int quantityToTrade = generateQuantity(traderType);
    double priceToTrade = generateRandomPrice(curentMarketPrice);



    return Order(orderID,BuyOrSellSide,typeOfOrder,priceToTrade,quantityToTrade);

}






Trader::Trader(int id, typeOfTrader type):traderID(id),traderType(type)
{}
    

double Trader::generateRandomPrice(double priceLevel) {

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> distribution(priceLevel*0.99, priceLevel*1.01);
    double priceToTradeAt = distribution(gen);
    priceToTradeAt = std::round(priceToTradeAt*100)/100.0;
    return priceToTradeAt;
}

int Trader::generateQuantity(typeOfTrader type) {

    std::random_device rd;
    std::mt19937 gen(rd());
    int quantitytoTrade = 0;
    if (type==typeOfTrader::Retail||type==typeOfTrader::Momentum) {
        std::uniform_int_distribution<int> distribution(0, 60);
         quantitytoTrade = distribution(gen);
    } else if (type==typeOfTrader::Whale) {

        std::uniform_int_distribution<int> distribution(1000, 50000);
         quantitytoTrade = distribution(gen);
    }
    return quantitytoTrade;

}