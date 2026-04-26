#pragma once
#include "issubscriber.h"
#include <unordered_map>
#include <string>

typedef struct Chart {
    // OHLCV format (Open, high, low, close, volume)
    double open = 0.0;
    double high = 0.0;
    double low = 0.0;
    double close = 0.0;
    double volume = 0.0;
    long long ticks = 0;
};

