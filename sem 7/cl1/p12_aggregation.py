# 12. Retail sales - aggregation by region
import pandas as pd, matplotlib.pyplot as plt

df = pd.read_csv("data/Retail_Sales_Data.csv")
print(df.head(), df.info(), sep="\n")

by_region = df.groupby("Region").SalesAmount.sum().sort_values(ascending=False)   # total per region
print(by_region.round(2))
print("Top region:", by_region.idxmax())

fig, ax = plt.subplots(1, 2, figsize=(11, 4))
by_region.plot.bar(ax=ax[0], title="Sales by region")
by_region.plot.pie(ax=ax[1], autopct="%1.0f%%", title="Share"); plt.show()

combo = df.groupby(["Region", "ProductCategory"]).SalesAmount.sum().unstack()     # region x category
print(combo.round(2))
combo.plot.bar(title="Region vs category (grouped)"); plt.show()
combo.plot.bar(stacked=True, title="Region vs category (stacked)"); plt.show()
