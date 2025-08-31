#include "marketSim.hpp"
#include "Order.hpp"
#include <thread>
#include <iostream>
#include <chrono>





marketSim::marketSim() {




};
void marketSim::runSimulation() {

    using namespace std::chrono;
    using namespace std::literals::chrono_literals;

    auto ticktime = 100ms;
    bool isMarketRunning = true;


    while (isMarketRunning) {


        auto start = high_resolution_clock::now();

        std::cout << "Perform orderbook things\n";

        auto end = high_resolution_clock::now();
        auto duration = end - start;

        if (duration < ticktime) {
            std::this_thread::sleep_for(ticktime - duration);
        }




    }




}