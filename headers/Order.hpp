#pragma once
#include <chrono>
#include <string>

enum class orderSide{BUY,SELL};
enum class OrderType { Market, Limit};

class Order{

private:
    int orderID;
    orderSide side;
    OrderType type;
    double price;
    int quantity;
    std::chrono::high_resolution_clock::time_point timestamp;


public:
    Order(int orderID, orderSide side, OrderType type, double price, int quantity);


    int getOrderID() const;
    orderSide getSide() const;
    OrderType getType() const;
    double getPrice() const;
    int getQuantity() const;
    std::chrono::high_resolution_clock::time_point getTimestamp() const;

    void setPrice(double newPrice);
    void setQuantity(int newQuantity);
    void setTimestamp(std::chrono::high_resolution_clock::time_point newTimestamp);


};