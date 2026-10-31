# 5B. AdaBoost, Gradient Boosting, XGBoost on Iris + voting ensemble
import pandas as pd
from sklearn.ensemble import AdaBoostClassifier, GradientBoostingClassifier, VotingClassifier
from xgboost import XGBClassifier
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score, precision_score, recall_score, f1_score

df = pd.read_csv("data/Iris.csv")
X, y = df.drop(columns="species"), df["species"]
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=1)

ada = AdaBoostClassifier(n_estimators=100, random_state=1)
gbm = GradientBoostingClassifier(random_state=1)
xgb = XGBClassifier(eval_metric="mlogloss", random_state=1)
models = {"AdaBoost": ada, "GBM": gbm, "XGBoost": xgb,
          "Hard voting": VotingClassifier([("a", ada), ("g", gbm), ("x", xgb)], voting="hard"),
          "Soft voting": VotingClassifier([("a", ada), ("g", gbm), ("x", xgb)], voting="soft")}

rows = []
for name, m in models.items():
    p = m.fit(X_train, y_train).predict(X_test)
    rows.append([name, accuracy_score(y_test, p), precision_score(y_test, p, average="macro"),
                 recall_score(y_test, p, average="macro"), f1_score(y_test, p, average="macro")])
print(pd.DataFrame(rows, columns=["Model", "Accuracy", "Precision", "Recall", "F1"]).round(3).to_string(index=False))
