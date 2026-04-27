#include "price_tracker.h"
#include <iostream>


void price_tracker::on_price(const price_packet& p) {
    // First time seing this symbol, create a struct
    if (data_.find(p.symbol) == data_.end()) {
        Chart new_data;
        o.open = p.price;
        o.low = p.price;
        o.close = p.price;
        data_[symbol] = o;
    }
    // get reference to this symbol
    Chart& new_data = data_[p.symbol];

    // update every tick
    o.close = p.price;
    o.volume += p.volume; 
    o.ticks++;

    if (p.price > o.high) o.high = p.price;
    if (p.price < o.low)  o.low  = p.price;
}

void price_tracker::print_all() {
    std::cout << "\n===Price Tracker ===\n"

    for (const auto& [symbol, o] : data_) {
        std::cout << symbol
                  << " open: " << o.open
                  << " high: " << o.high
                  << " low: " << o.low
                  << " close: " << o.close
                  << "\n";
    }
}

const Chart& PriceTracker::get(const std::string& symbol) const {
    return data_.at(symbol);
}