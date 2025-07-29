#include "OrderBook.hpp";
#include <chrono>
#include <string>
#include "Order.hpp"
#include <map>


void OrderBook::matchOrder(Order& orderToMatch) {

    if (orderToMatch.getSide()==orderSide::BUY) {
        for (auto it = sellOrders.begin(); it != sellOrders.end() && orderToMatch.getQuantity() > 0;) {

            auto& [priceatLevel,sellOrdersAtLevel] = *it;

           if (orderToMatch.getPrice()>=priceatLevel) {


               //iterate through sell orders at this price level
               for (auto indiSellOrder =sellOrdersAtLevel.begin(); indiSellOrder != sellOrdersAtLevel.end() && orderToMatch.getQuantity() > 0;) {

                   int tradedQuantity = 0;
                   if (orderToMatch.getQuantity()>=indiSellOrder->getQuantity()) {
                       tradedQuantity = orderToMatch.getQuantity() - indiSellOrder->getQuantity();
                   }else {
                       tradedQuantity = indiSellOrder->getQuantity() - orderToMatch.getQuantity();
                   }

                   orderToMatch.s


               }


           }



        }




    }



}