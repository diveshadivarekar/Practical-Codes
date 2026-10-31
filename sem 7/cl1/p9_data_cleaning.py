# 9. Telecom customer churn - data cleaning & preparation
import pandas as pd, numpy as np
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler

df = pd.read_csv("data/Telecom_Customer_Churn.csv")                 # 1. import
print(df.shape); print(df.info()); print(df.isna().sum())            # 2. explore

df = df.drop_duplicates()                                            # 4. duplicates
df["gender"] = df.gender.str.title()                                 # 5. fix inconsistent text (male/MALE -> Male)
df["TotalCharges"] = pd.to_numeric(df.TotalCharges, errors="coerce") # 6. correct dtype (" " -> NaN)

df["MonthlyCharges"] = df.MonthlyCharges.fillna(df.MonthlyCharges.median())   # 3. missing values
df["TotalCharges"] = df.TotalCharges.fillna(df.TotalCharges.median())

q1, q3 = df.MonthlyCharges.quantile([.25, .75])                      # 7. outliers (IQR)
df = df[df.MonthlyCharges.between(q1 - 1.5 * (q3 - q1), q3 + 1.5 * (q3 - q1))]

df["AvgChargePerMonth"] = df.TotalCharges / (df.tenure + 1)          # 8. feature engineering
df["IsLongTerm"] = (df.Contract != "Month-to-month").astype(int)
df["Churn"] = df.Churn.map({"Yes": 1, "No": 0})

df = pd.get_dummies(df.drop(columns="customerID"), drop_first=True)  # encode categoricals
num = ["tenure", "MonthlyCharges", "TotalCharges", "AvgChargePerMonth"]
df[num] = StandardScaler().fit_transform(df[num])                    # 9. scale

X, y = df.drop(columns="Churn"), df.Churn                            # 10. split
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=1)
print("Train/test:", X_train.shape, X_test.shape)

df.to_csv("data/Telecom_Cleaned.csv", index=False)                   # 11. export
print("Saved data/Telecom_Cleaned.csv")
