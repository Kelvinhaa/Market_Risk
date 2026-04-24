#pragma once
#include "issubscriber.h"
#include <unordered_map>
#include <string>

class Data {
    double open = 0.0;
    double high = 0.0;
    double low = 0.0;
    double close = 0.0;
    double volume = 0.0;
    double open = 0.0;
    

};

class Price_Tracker {
public: 
    void on_price(const price_packet& p) override;
    std::string name() const override {
        return "PriceTracker"
    }

    void print_all();

private:
    std::unordered_map <std::string, Data> data_;
}