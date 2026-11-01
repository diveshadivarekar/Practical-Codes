# 8. OpenWeatherMap API -> DataFrame -> clean -> analyze -> plot
# Get a free key at https://openweathermap.org/api and paste it below.
# With no key, the script uses data/weather_sample.json (same format as the API reply).
import json, requests, pandas as pd, matplotlib.pyplot as plt, seaborn as sns
import sys

API_KEY, CITY = "7b9809e16822067b61db12489b9ebe47", "Pune"
if API_KEY:
    url = f"https://api.openweathermap.org/data/2.5/forecast?q={CITY}&appid={API_KEY}&units=metric"
    data = requests.get(url).json()
    if "list" not in data:   # API returned an error (bad/inactive key, wrong city...)
        print("API error:", data.get("message", data), "-> using sample data instead")
        data = json.load(open("data/weather_sample.json"))
else:
    data = json.load(open("data/weather_sample.json"))

# Extract attributes
df = pd.DataFrame([{"time": x["dt_txt"], "temp": x["main"]["temp"], "humidity": x["main"]["humidity"],
                    "wind": x["wind"]["speed"], "rain": x.get("rain", {}).get("3h", 0)} for x in data["list"]])
df["time"] = pd.to_datetime(df["time"])
df = df.dropna().set_index("time")                       # clean

print(df.describe().round(2))                            # avg / max / min
daily = df.resample("D").agg({"temp": ["mean", "max", "min"], "rain": "sum", "wind": "mean"})
print(daily.head())

fig, ax = plt.subplots(1, 3, figsize=(15, 4))
df.temp.plot(ax=ax[0], title="Temperature (C)")
daily["rain"].plot.bar(ax=ax[1], title="Daily rain (mm)", xticks=[])
ax[2].scatter(df.temp, df.humidity); ax[2].set(title="Temp vs humidity", xlabel="temp", ylabel="humidity")
plt.tight_layout(); plt.show()
sns.heatmap(df.corr(), annot=True, cmap="coolwarm"); plt.title("Correlation"); plt.show()