# 11. AQI trends with matplotlib
import pandas as pd, matplotlib.pyplot as plt

df = pd.read_csv("data/City_Air_Quality.csv", parse_dates=["Date"])
print(df.head(), df.describe(), sep="\n")

plt.figure(figsize=(10, 4)); plt.plot(df.Date, df.AQI, color="purple")           # overall trend
plt.title("AQI over time"); plt.xlabel("Date"); plt.ylabel("AQI"); plt.show()

fig, ax = plt.subplots(3, 1, figsize=(10, 7), sharex=True)                        # each pollutant
for a, col in zip(ax, ["PM2.5", "PM10", "CO"]):
    a.plot(df.Date, df[col]); a.set_ylabel(col)
plt.suptitle("Pollutants over time"); plt.show()

monthly = df.groupby(df.Date.dt.month)[["PM2.5", "PM10"]].mean()                  # bar plot
monthly.plot.bar(title="Monthly average PM"); plt.xlabel("Month"); plt.legend(); plt.show()

df[["PM2.5", "PM10", "CO"]].plot.box(title="Pollutant distributions"); plt.show() # box plot

plt.scatter(df["PM2.5"], df.AQI, c=df.PM10, cmap="viridis", alpha=.7)             # scatter
plt.colorbar(label="PM10"); plt.xlabel("PM2.5"); plt.ylabel("AQI"); plt.title("AQI vs PM2.5"); plt.show()
