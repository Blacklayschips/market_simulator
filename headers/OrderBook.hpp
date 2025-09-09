#pragma once
#include <chrono>
#include <string>
#include "Order.hpp"
#include <map>


struct tradeRecord {

    int buyOrderID;
    int sellOrderID;
    double price;
    int quantity;
    std::chrono::system_clock::time_point timestamp;



};


class  OrderBook {

    public:
    void addOrder(const Order& newOrder);
    void removeOrder(const Order& order);
    void matchOrder(Order&  orderToMatch,double& marketPrice);
    void matchMarketOrder(Order&  orderToMatch,double& marketPrice);





    void PrintOrderBook() const;
    void printTradeHistory() const;
    private:
    std::map<double, std::vector<Order>,std::greater<>> buyOrders;
    std::map<double, std::vector<Order>> sellOrders;
    std::vector<tradeRecord> tradeHistory;



    void recordTrade(int buyId, int sellId, double price, int qty);



    void matchBuyAndSellOrder(const Order& order);


};//