# 7. Load sales data from CSV, Excel, JSON -> clean -> unify -> analyze -> plot
import pandas as pd, matplotlib.pyplot as plt

# 1. Load
csv, xls, js = pd.read_csv("data/sales.csv"), pd.read_excel("data/sales.xlsx"), pd.read_json("data/sales.json")
# 2. Explore
for n, d in [("CSV", csv), ("Excel", xls), ("JSON", js)]:
    print(n, d.shape, "missing:", d.isna().sum().sum(), "duplicates:", d.duplicated().sum())

# 3-4. Unify + clean
df = pd.concat([csv, xls, js], ignore_index=True).drop_duplicates()
df["UnitPrice"] = df["UnitPrice"].fillna(df["UnitPrice"].median())
df["Date"] = pd.to_datetime(df["Date"])

# 5. Transform: derive new columns
df["Sales"] = df.Quantity * df.UnitPrice
df["Month"] = df.Date.dt.to_period("M").astype(str)

# 6. Analyze
print("Total sales:", round(df.Sales.sum(), 2), "| Avg order value:", round(df.Sales.mean(), 2))
print(df.groupby("Category").Sales.sum().round(2))

# 7. Visualize
fig, ax = plt.subplots(1, 3, figsize=(15, 4))
df.groupby("Category").Sales.sum().plot.bar(ax=ax[0], title="Sales by category")
df.groupby("Category").Sales.sum().plot.pie(ax=ax[1], autopct="%1.0f%%", title="Share")
df.boxplot("Sales", by="Category", ax=ax[2]); plt.tight_layout(); plt.show()
