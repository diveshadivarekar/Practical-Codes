# 2A. Uber fare prediction - Linear, Ridge, Lasso
import numpy as np, pandas as pd, matplotlib.pyplot as plt, seaborn as sns
from sklearn.linear_model import LinearRegression, Ridge, Lasso
from sklearn.model_selection import train_test_split
from sklearn.metrics import r2_score, mean_squared_error

# 1. Pre-process
df = pd.read_csv("data/uber.csv").dropna()
df = df[(df.pickup_latitude != 0) & (df.fare_amount > 0)]
# distance (km) from coordinates
df["distance"] = np.sqrt(((df.dropoff_latitude - df.pickup_latitude) * 111) ** 2 +
                         ((df.dropoff_longitude - df.pickup_longitude) * 84) ** 2)
df["hour"] = pd.to_datetime(df.pickup_datetime).dt.hour

# 2. Outliers (boxplot + IQR rule)
sns.boxplot(x=df.fare_amount); plt.title("Fare outliers"); plt.show()
q1, q3 = df.fare_amount.quantile([.25, .75])
df = df[df.fare_amount.between(q1 - 1.5 * (q3 - q1), q3 + 1.5 * (q3 - q1))]

# 3. Correlation
cols = ["fare_amount", "distance", "passenger_count", "hour"]
sns.heatmap(df[cols].corr(), annot=True, cmap="coolwarm"); plt.show()

# 4. Models
X, y = df[["distance", "passenger_count", "hour"]], df.fare_amount
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=1)
models = {"Linear": LinearRegression(), "Ridge": Ridge(alpha=1.0), "Lasso": Lasso(alpha=0.01)}

# 5. Evaluate & compare
for name, m in models.items():
    p = m.fit(X_train, y_train).predict(X_test)
    print(f"{name:7s} R2={r2_score(y_test, p):.3f}  RMSE={np.sqrt(mean_squared_error(y_test, p)):.3f}")
