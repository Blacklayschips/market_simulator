#pragma once
#include <chrono>
#include <string>
#include "Order.hpp"
#include <map>

class  OrderBook {

    public:
    void addOrder(const Order& newOrder);
    void removeOrder(const Order& order);
    void matchOrder(const Order& orderToMatch);
    void PrintOrderBook() const;

    private:
    std::map<double, std::vector<Order>,std::greater<>> buyOrders;
    std::map<double, std::vector<Order>> sellOrders;

    void matchBuyAndSellOrder(const Order& order);


};