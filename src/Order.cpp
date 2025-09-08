#include "Order.hpp"

Order::Order(int orderID, orderSide side, OrderType type, double price, int quantity):
    orderID(orderID),side(side),type(type),price(price),quantity(quantity),  timestamp(std::chrono::high_resolution_clock::now()){}

int Order::getOrderID() const {
    return orderID;
}

orderSide Order::getSide() const {
    return side;
}

OrderType Order::getType() const {
    return type;
}

double Order::getPrice() const {
    return price;
}

int Order::getQuantity() const {
    return quantity;
}

std::chrono::high_resolution_clock::time_point Order::getTimestamp() const {
    return timestamp;
}

void Order::setPrice(double newPrice) {
    price = newPrice;
}
void Order::setQuantity(int newQuantity) {
    quantity = newQuantity;
}
void Order::setTimestamp(std::chrono::high_resolution_clock::time_point newTimestamp) {
    timestamp = newTimestamp;
}//