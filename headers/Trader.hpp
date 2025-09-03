#pragma once
#include "Order.hpp"
#include <optional>

enum class typeOfTrader {
    Retail,
    Whale,
    Momentum

};

class Trader {

public:
    Trader(int id,double marketPrice,typeOfTrader type);
    std::optional<Order> generateOrder(int orderID,double curentMarketPrice,int marketDirectionCountUp,int marketDirectionCountDown);

private:
    int traderID;
    typeOfTrader traderType;
    int priceChosen;
    int quantity;
    double generateRandomPrice(double priceLevel);
    int generateQuantity(typeOfTrader trader_type);


};



