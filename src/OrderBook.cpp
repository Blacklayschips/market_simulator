#include "OrderBook.hpp";
#include <chrono>
#include <string>
#include "Order.hpp"
#include <map>


void OrderBook::matchOrder(Order orderToMatch) {

    if (orderToMatch.getSide()==orderSide::BUY) {
        for (auto it = sellOrders.begin(); it != sellOrders.end() && orderToMatch.getQuantity() > 0;) {

            auto& [priceatLevel,sellOrdersAtLevel] = *it;

           if (orderToMatch.getPrice()>=priceatLevel) {


               //iterate through sell orders at this price level
               for (auto indiSellOrder =sellOrdersAtLevel.begin(); indiSellOrder != sellOrdersAtLevel.end() && orderToMatch.getQuantity() > 0;) {

                   int tradedQuantity = 0;
                   //gets the difference in orders
                   if (orderToMatch.getQuantity()>=indiSellOrder->getQuantity()) {
                       tradedQuantity = indiSellOrder->getQuantity();
                   }else {
                       tradedQuantity = orderToMatch.getQuantity();
                   }

                   orderToMatch.setQuantity(orderToMatch.getQuantity()-tradedQuantity);
                   indiSellOrder->setQuantity(indiSellOrder->getQuantity()-tradedQuantity);


                   if (indiSellOrder->getQuantity()==0) {
                      indiSellOrder = sellOrdersAtLevel.erase(indiSellOrder);
                   }else {
                       ++indiSellOrder;

                   }


               }

                //when sell orders at the level are empty delete the price level
               if (sellOrdersAtLevel.empty()) {
                   it = sellOrders.erase(it);
               }else {
                   ++it;
               }


           }else {
               break;
           }



        }




    }



}