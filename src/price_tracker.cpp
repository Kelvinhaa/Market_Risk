#include "price_tracker.h"
#include <iostream>


void price_tracker::on_price(const price_packet& p) {
    if (data_.find(p.symbol) == data_.end()) {
        Chart new_data;
        o.open = p.price;
        o.low = p.price;
        o.close = p.price;
    }
    Chart& new_data = data_.symbol;
    
    new_data.ticks++;

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