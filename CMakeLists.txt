cmake_minimum_required(VERSION 3.16)
project(market_data_engine CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra)

add_executable(market_data_engine
    src/main.cpp
    src/dispatcher.cpp
    src/risk_monitor.cpp
    src/price_tracker.cpp
    src/logger.cpp
)

target_include_directories(market_data_engine PRIVATE include)