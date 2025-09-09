#pragma once
#include "Order.hpp"
#include <optional>

enum class typeOfTrader {
    Retail,
    Whale,
    Momentum,
    dipBuyer
};

class Trader {

public:
    Trader(int id,typeOfTrader type);
    std::optional<Order> generateOrder(int orderID,double curentMarketPrice,int marketDirectionCountUp,int marketDirectionCountDown);
    int getTraderID()const;
    typeOfTrader getType()const;
private:
    int traderID;
    typeOfTrader traderType;
    double generateRandomPrice(double priceLevel);
    int generateQuantity(typeOfTrader trader_type);


};



//