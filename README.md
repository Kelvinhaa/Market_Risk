# Market Data Engine

A low-latency market data processing engine built in C++ that ingests real-time equity price feeds, routes them to decoupled subscriber modules, and computes live risk metrics including Sharpe Ratio and volatility.

Built as a demonstration of systems-level OOP design, publisher-subscriber architecture, and quantitative financial analytics.

---

## Architecture

```
CSV / Price Feed
      │
      ▼
 Dispatcher
      │
      ├──→  Logger         prints every tick (audit trail)
      ├──→  PriceTracker   aggregates OHLCV per symbol
      └──→  RiskMonitor    computes Sharpe Ratio + volatility
```

The `Dispatcher` is the core — it receives raw price packets and fans them out to registered subscribers. Each subscriber is fully decoupled and knows nothing about the others. New subscribers can be added in under 10 lines of code without modifying any existing logic.

---

## Features

- **Publisher-Subscriber Architecture** — price packets routed to global or symbol-specific subscribers
- **Pure Virtual Interface** — `ISubscriber` enforces a consistent contract across all consumers
- **OHLCV Tracking** — open, high, low, close, volume aggregated per symbol across the full price history
- **Rolling Risk Metrics** — Sharpe Ratio and return volatility computed incrementally per symbol
- **S&P 500 Benchmarking** — SPY used as market proxy to compare individual equity risk-adjusted returns
- **CSV Ingestion Pipeline** — loads and normalises historical price data from Yahoo Finance

---

## Project Structure

```
market_data_engine/
├── include/
│   ├── price_packet.h       # Core data struct passed between all components
│   ├── isubscriber.h        # Pure virtual interface all subscribers implement
│   ├── dispatcher.h         # Routes packets to registered subscribers
│   ├── risk_monitor.h       # Computes Sharpe Ratio, volatility, mean return
│   ├── price_tracker.h      # Tracks OHLCV metrics per symbol
│   └── logger.h             # Prints every incoming price packet
├── src/
│   ├── main.cpp             # Entry point — wires subscribers, loads CSV
│   ├── dispatcher.cpp       # Publish and dispatch logic
│   ├── risk_monitor.cpp     # Risk metric computation
│   ├── price_tracker.cpp    # OHLCV aggregation
│   └── logger.cpp           # Tick logging
├── data/
│   └── prices.csv           # Historical price feed (Yahoo Finance)
└── CMakeLists.txt
```

---

## Build & Run

**Requirements:** C++17, CMake 3.16+

```bash
# Clone the repository
git clone git@github.com:Kelvinhaa/Market_Risk.git
cd market-data-engine

# Build
cmake -B build
cmake --build build

# Run
./build/market_data_engine
```

---

## Data Setup

Download historical price data using the provided Python script:

```bash
pip install yfinance
python3 scripts/fetch_data.py
```

Or download manually from [Yahoo Finance](https://finance.yahoo.com):
1. Search for a ticker (AAPL, TSLA, SPY)
2. Click **Historical Data** → set range → **Download**
3. Reformat columns to `symbol, price, volume`
4. Save to `data/prices.csv`

Expected CSV format:
```
symbol,price,volume
AAPL,189.42,1200
AAPL,190.15,800
TSLA,242.10,2000
SPY,542.10,5000
```

---

## Sample Output

```
[AAPL]  price: 189.42  volume: 1200
[AAPL]  price: 190.15  volume: 800
[TSLA]  price: 242.10  volume: 2000
[SPY]   price: 542.10  volume: 5000

=== Price Tracker ===
AAPL   open: 189.42   high: 190.15   low: 188.90   close: 190.01   volume: 2950    ticks: 3
TSLA   open: 242.10   high: 243.80   low: 241.55   close: 243.80   volume: 5300    ticks: 3
SPY    open: 542.10   high: 543.80   low: 541.90   close: 541.90   volume: 15500   ticks: 3

=== Risk Monitor: AAPL ===
Ticks        : 252
Mean Return  : 0.0012  (+0.12% per day)
Volatility   : 0.0183  (1.83% daily)
Sharpe Ratio : 1.24

=== Risk Monitor: TSLA ===
Ticks        : 252
Mean Return  : 0.0018
Volatility   : 0.0341
Sharpe Ratio : 0.87

=== Risk Monitor: SPY ===
Ticks        : 252
Mean Return  : 0.0008
Volatility   : 0.0094
Sharpe Ratio : 1.61
```

## Author

Minh Hoang Ha
