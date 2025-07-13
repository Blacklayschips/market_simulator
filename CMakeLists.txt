cmake_minimum_required(VERSION 3.20)
project(marketSimulator)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)       # will work even if 'include/' is empty

file(GLOB SOURCES "src/*.cpp")     # right now, only src/main.cpp exists

add_executable(marketSimulator ${SOURCES}
        src/Order.cpp
        headers/Order.hpp)
