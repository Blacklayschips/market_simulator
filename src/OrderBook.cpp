#include "OrderBook.hpp";
#include <chrono>
#include <string>
#include "Order.hpp"
#include <map>
#include <iostream>
#include <ctime>



void OrderBook::recordTrade(int buyID, int sellID, double price, int quantity)  {

    tradeRecord trade{
        buyID,
        sellID,
        price,
        quantity,
        std::chrono::system_clock::now()
    };
    tradeHistory.push_back(trade);


}

void OrderBook::printTradeHistory() const {

    for (const auto& trade : tradeHistory) {
        std::time_t t = std::chrono::system_clock::to_time_t(trade.timestamp);
        std::cout<<"Trade BuyID: "<<trade.buyOrderID<<" Trade SellID: "<<trade.sellOrderID<<" Price : "<<trade.price<<" Quantity: "<<trade.quantity<<" Transaction time "<< std::ctime(&t);


    }


}
void OrderBook::PrintOrderBook() const {
    std::cout << "\n      ORDER BOOK      \n";


    std::cout << "Buy orders:" << '\n';
    std::cout << "      Volume" << "          Price" << '\n';


    for (auto it = buyOrders.begin(); it != buyOrders.end(); ++it) {
        double price = it->first;
        const std::vector<Order> &ordersAtLevel = it->second;

        int totalQuant = 0;
        for (int i = 0; i < ordersAtLevel.size(); ++i) {
            totalQuant += ordersAtLevel.at(i).getQuantity();
        }

        std::cout << "       " << totalQuant << "               " << price << '\n';
    }

    std::cout << '\n';
    std::cout << "Sell orders:" << '\n';
    std::cout << "      Volume" << "          Price" << '\n';


    for (auto it = sellOrders.begin(); it != sellOrders.end(); ++it) {
        double price = it->first;
        const std::vector<Order> &ordersAtLevel = it->second;

        int totalQuant = 0;
        for (int i = 0; i < ordersAtLevel.size(); ++i) {
            totalQuant += ordersAtLevel.at(i).getQuantity();
        }

        std::cout << "       " << totalQuant << "               " << price << '\n';
    }
}


void OrderBook::matchMarketOrder(Order& marketOrder) {
    if (marketOrder.getSide()==orderSide::BUY) {
        for (auto it = sellOrders.begin(); it != sellOrders.end() && marketOrder.getQuantity() > 0;) {
            auto &[priceatLevel,sellOrdersAtLevel] = *it;


            for (auto indiSellOrder = sellOrdersAtLevel.begin();
                    indiSellOrder != sellOrdersAtLevel.end() && marketOrder.getQuantity() > 0;) {

                int tradedQuantity = 0;
                //gets the difference in orders
                if (marketOrder.getQuantity() >= indiSellOrder->getQuantity()) {
                    tradedQuantity = indiSellOrder->getQuantity();
                } else {
                    tradedQuantity = marketOrder.getQuantity();
                }

                recordTrade(marketOrder.getOrderID(), indiSellOrder->getOrderID(), indiSellOrder->getPrice(), tradedQuantity);
                marketOrder.setQuantity(marketOrder.getQuantity() - tradedQuantity);
                indiSellOrder->setQuantity(indiSellOrder->getQuantity() - tradedQuantity);


                if (indiSellOrder->getQuantity() == 0) {
                    indiSellOrder = sellOrdersAtLevel.erase(indiSellOrder);
                } else {
                    ++indiSellOrder;
                }
                    }

            //when sell orders at the level are empty delete the price level
            if (sellOrdersAtLevel.empty()) {
                it = sellOrders.erase(it);
            } else {
                ++it;
            }

        }
    }else if (marketOrder.getSide() == orderSide::SELL) {
        for (auto it = buyOrders.begin(); it != buyOrders.end() && marketOrder.getQuantity() > 0;) {
            auto &[priceatLevel, buyOrdersAtLevel] = *it;

            for (auto indiBuyOrder = buyOrdersAtLevel.begin();
                 indiBuyOrder != buyOrdersAtLevel.end() && marketOrder.getQuantity() > 0;) {

                int tradedQuantity = 0;
                // gets the difference in orders
                if (marketOrder.getQuantity() >= indiBuyOrder->getQuantity()) {
                    tradedQuantity = indiBuyOrder->getQuantity();
                } else {
                    tradedQuantity = marketOrder.getQuantity();
                }

                recordTrade(indiBuyOrder->getOrderID(), marketOrder.getOrderID(), indiBuyOrder->getPrice(), tradedQuantity);
                marketOrder.setQuantity(marketOrder.getQuantity() - tradedQuantity);
                indiBuyOrder->setQuantity(indiBuyOrder->getQuantity() - tradedQuantity);

                if (indiBuyOrder->getQuantity() == 0) {
                    indiBuyOrder = buyOrdersAtLevel.erase(indiBuyOrder);
                } else {
                    ++indiBuyOrder;
                }
                 }

            // when buy orders at the level are empty delete the price level
            if (buyOrdersAtLevel.empty()) {
                it = buyOrders.erase(it);
            } else {
                ++it;
            }
        }
    }

    //any market not fufilled are not added to orderbook
}







void OrderBook::matchOrder(Order &orderToMatch) {

    if (orderToMatch.getType()==OrderType::Market) {
        matchMarketOrder(orderToMatch);
        return;
    }


    if (orderToMatch.getSide() == orderSide::BUY) {
        for (auto it = sellOrders.begin(); it != sellOrders.end() && orderToMatch.getQuantity() > 0;) {
            auto &[priceatLevel,sellOrdersAtLevel] = *it;

            if (orderToMatch.getPrice() >= priceatLevel) {
                //iterate through sell orders at this price level
                for (auto indiSellOrder = sellOrdersAtLevel.begin();
                     indiSellOrder != sellOrdersAtLevel.end() && orderToMatch.getQuantity() > 0;) {
                    int tradedQuantity = 0;
                    //gets the difference in orders
                    if (orderToMatch.getQuantity() >= indiSellOrder->getQuantity()) {
                        tradedQuantity = indiSellOrder->getQuantity();
                    } else {
                        tradedQuantity = orderToMatch.getQuantity();
                    }


                    recordTrade(orderToMatch.getOrderID(),indiSellOrder->getOrderID(),orderToMatch.getPrice(),tradedQuantity);


                    orderToMatch.setQuantity(orderToMatch.getQuantity() - tradedQuantity);
                    indiSellOrder->setQuantity(indiSellOrder->getQuantity() - tradedQuantity);


                    if (indiSellOrder->getQuantity() == 0) {
                        indiSellOrder = sellOrdersAtLevel.erase(indiSellOrder);
                    } else {
                        ++indiSellOrder;
                    }
                }

                //when sell orders at the level are empty delete the price level
                if (sellOrdersAtLevel.empty()) {
                    it = sellOrders.erase(it);
                } else {
                    ++it;
                }
            } else {
                break;
            }
        }
    } else if (orderToMatch.getSide() == orderSide::SELL) {
        for (auto it = buyOrders.begin(); it != buyOrders.end() && orderToMatch.getQuantity() > 0;) {
            auto &[priceatLevel,buyOrdersAtLevel] = *it;

            if (orderToMatch.getPrice() <= priceatLevel) {
                for (auto indiBuyOrder = buyOrdersAtLevel.begin();
                     indiBuyOrder != buyOrdersAtLevel.end() && orderToMatch.getQuantity() > 0;) {
                    int tradedQuantity = 0;
                    //gets the difference in orders
                    if (orderToMatch.getQuantity() >= indiBuyOrder->getQuantity()) {
                        tradedQuantity = indiBuyOrder->getQuantity();
                    } else {
                        tradedQuantity = orderToMatch.getQuantity();
                    }

                    recordTrade(indiBuyOrder->getOrderID(),orderToMatch.getOrderID(),orderToMatch.getPrice(),tradedQuantity);

                    orderToMatch.setQuantity(orderToMatch.getQuantity() - tradedQuantity);
                    indiBuyOrder->setQuantity(indiBuyOrder->getQuantity() - tradedQuantity);


                    if (indiBuyOrder->getQuantity() == 0) {
                        indiBuyOrder = buyOrdersAtLevel.erase(indiBuyOrder);
                    } else {
                        ++indiBuyOrder;
                    }
                }
                if (buyOrdersAtLevel.empty()) {
                    it = buyOrders.erase(it);
                } else {
                    ++it;
                }
            } else {
                break;
            }
        }
    }


    //any leftover orders that havent been filled get added to the orderbook
    if (orderToMatch.getQuantity() > 0) {
        if (orderToMatch.getSide() == orderSide::BUY) {
            buyOrders[orderToMatch.getPrice()].push_back(orderToMatch);
        } else {
            sellOrders[orderToMatch.getPrice()].push_back(orderToMatch);
        }
    }
}
