# 10. Real estate - data wrangling
import pandas as pd

df = pd.read_csv("data/RealEstate_Prices.csv")
# 1. clean column names: "Area (sqft)" -> "area_sqft"
df.columns = df.columns.str.lower().str.replace(r"[^a-z0-9]+", "_", regex=True).str.strip("_")
print(df.columns.tolist())

df["area_sqft"] = df.area_sqft.fillna(df.area_sqft.median())          # 2. missing values
df["sale_date"] = pd.to_datetime(df.sale_date)

# 3. merge with extra data (neighborhood info)
info = pd.DataFrame({"neighborhood": ["Kothrud", "Baner", "Hinjewadi", "Wakad"], "metro_km": [2, 5, 8, 7]})
df = df.merge(info, on="neighborhood", how="left")

# 4. filter / subset
sub = df[(df.sale_date >= "2023-01-01") & (df.property_type == "House")]
print("Houses sold since 2023:", len(sub))

df = pd.get_dummies(df, columns=["property_type"])                    # 5. encode categoricals
print(df.groupby("neighborhood").sale_price.mean().round())          # 6. aggregate

q1, q3 = df.sale_price.quantile([.25, .75])                           # 7. outliers (IQR)
df = df[df.sale_price.between(q1 - 1.5 * (q3 - q1), q3 + 1.5 * (q3 - q1))]
print("Rows after outlier removal:", len(df))
