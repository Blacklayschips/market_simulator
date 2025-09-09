#pragma once
#include <chrono>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <iostream>

struct Candlestick {
    double open;
    double close;
    double high;
    double low;
    int volume;
    std::chrono::system_clock::time_point timestamp;
};

inline void writeCandleToCSV(const Candlestick& candle, const std::string& filename = "candles.csv") {
    static bool headerWritten = false;

    std::ofstream file(filename, std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Error: could not open " << filename << "\n";
        return;
    }

    if (!headerWritten) {
        file << "Open,High,Low,Close,Volume,Timestamp\n";
        headerWritten = true;
    }

    std::time_t t = std::chrono::system_clock::to_time_t(candle.timestamp);
    file << candle.open << ","<< candle.high << ","<< candle.low << ","<< candle.close << ","<< candle.volume << ","<< std::put_time(std::localtime(&t), "%Y-%m-%d %H:%M:%S")<< "\n";
}
