#include "logger.h"
#include <iostream>

void Logger::on_price(const price_packet& p) {
    std::cout << "[" << p.symbol << "]"
              << "  price" << p.price
              << "  volume" << p.volume
              << "\n";
} 