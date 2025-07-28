cmake_minimum_required(VERSION 3.20)
project(marketSimulator)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES "src/*.cpp")

add_executable(marketSimulator ${SOURCES}
        headers/OrderBook.hpp
        src/OrderBook.cpp)


target_include_directories(marketSimulator PRIVATE headers)
