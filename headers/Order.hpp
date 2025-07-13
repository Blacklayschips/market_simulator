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

};