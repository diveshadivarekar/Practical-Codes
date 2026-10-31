# 13. Stock price time series - trend, moving average, seasonality, ARIMA forecast
import pandas as pd, matplotlib.pyplot as plt
from statsmodels.tsa.arima.model import ARIMA
from statsmodels.tsa.seasonal import seasonal_decompose

df = pd.read_csv("data/Stock_Prices.csv", parse_dates=["Date"], index_col="Date")   # date -> datetime index
print(df.head(), df.info(), sep="\n")

df.Close.plot(title="Closing price", figsize=(10, 4)); plt.show()

df["MA30"], df["MA90"] = df.Close.rolling(30).mean(), df.Close.rolling(90).mean()    # moving averages
df[["Close", "MA30", "MA90"]].plot(title="Moving averages", figsize=(10, 4)); plt.show()

seasonal_decompose(df.Close, model="additive", period=21).plot(); plt.show()          # ~monthly seasonality

print("Correlation Close vs Volume:", round(df.Close.corr(df.Volume), 3))             # correlation

train, test = df.Close[:-30], df.Close[-30:]                                          # ARIMA forecast
fc = ARIMA(train, order=(5, 1, 0)).fit().forecast(30)
plt.plot(train[-100:], label="train"); plt.plot(test, label="actual"); plt.plot(test.index, fc, label="forecast")
plt.legend(); plt.title("ARIMA(5,1,0) forecast"); plt.show()
