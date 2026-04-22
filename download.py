import yfinance as yf
import pandas as pd

tickers = ["AAPL", "TSLA", "SPY"]

with open("data/prices.csv", "w") as f:
    f.write("symbol,price,volume\n")
    for ticker in tickers:
        data = yf.download(ticker, period="3mo", interval="1d", group_by="column", progress=False)
        # yfinance can sometimes return MultiIndex columns; normalize to simple columns.
        if isinstance(data.columns, pd.MultiIndex):
            # Prefer the first level (Open/High/Low/Close/Volume).
            data.columns = data.columns.get_level_values(0)
        for _, row in data.iterrows():
            close = row.get("Close")
            volume = row.get("Volume")
            if pd.isna(close) or pd.isna(volume):
                continue
            f.write(f"{ticker},{float(close):.2f},{int(volume)}\n")

print("Data downloaded and saved to data/prices.csv")