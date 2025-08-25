#include "OrderBook.hpp";
#include <chrono>
#include <string>
#include "Order.hpp"
#include <map>
#include <iostream>




void OrderBook::matchOrder(Order& orderToMatch) {

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




    }else if (orderToMatch.getSide()==orderSide::SELL) {

        for (auto it = buyOrders.begin(); it != buyOrders.end() && orderToMatch.getQuantity() > 0;) {

            auto& [priceatLevel,buyOrdersAtLevel] = *it;

            if (orderToMatch.getPrice() <= priceatLevel) {

                for (auto indiBuyOrder =buyOrdersAtLevel.begin(); indiBuyOrder != buyOrdersAtLevel.end() && orderToMatch.getQuantity() > 0;) {



                    int tradedQuantity = 0;
                    //gets the difference in orders
                    if (orderToMatch.getQuantity()>=indiBuyOrder->getQuantity()) {
                        tradedQuantity = indiBuyOrder->getQuantity();
                    }else {
                        tradedQuantity = orderToMatch.getQuantity();
                    }

                    orderToMatch.setQuantity(orderToMatch.getQuantity()-tradedQuantity);
                    indiBuyOrder->setQuantity(indiBuyOrder->getQuantity()-tradedQuantity);


                    if (indiBuyOrder->getQuantity()==0) {
                        indiBuyOrder = buyOrdersAtLevel.erase(indiBuyOrder);
                    }else {
                        ++indiBuyOrder;
                    }


                }
                if (buyOrdersAtLevel.empty()) {
                    it = buyOrders.erase(it);
                } else {
                    ++it;
                }
            }else {
                break;
            }




        }





    }

    //any leftover orders that havent been filled get added to the orderbook
    if (orderToMatch.getQuantity()>0) {
        if (orderToMatch.getSide()==orderSide::BUY) {
            buyOrders[orderToMatch.getPrice()].push_back(orderToMatch);
        }else {
            sellOrders[orderToMatch.getPrice()].push_back(orderToMatch);
        }
    }


}