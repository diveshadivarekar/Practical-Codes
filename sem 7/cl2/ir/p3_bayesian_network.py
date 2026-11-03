# 3. Bayesian network for heart-disease diagnosis (pgmpy)
import pandas as pd
try:
    from pgmpy.models import DiscreteBayesianNetwork        # newer pgmpy
except ImportError:
    from pgmpy.models import BayesianNetwork as DiscreteBayesianNetwork   # older pgmpy
from pgmpy.inference import VariableElimination

df = pd.read_csv("data/heart_disease_uci.csv")
# works with different Kaggle versions of the file: rename columns / encode text if needed
df = df.rename(columns={"thalch": "thalach", "num": "target", "HeartDisease": "target"})
df["sex"] = df.sex.replace({"Male": 1, "Female": 0})
df["target"] = (df.target > 0).astype(int)                      # any disease level -> 1
df["cp"] = df.cp.astype("category").cat.codes
df["exang"] = df.exang.astype(str).str.lower().map({"true": 1, "false": 0, "1": 1, "0": 0, "1.0": 1, "0.0": 0})
df = df[["age", "sex", "cp", "trestbps", "chol", "exang", "thalach", "target"]].dropna()   # drop missing rows
df = df[df.chol > 0].astype(float)                              # chol = 0 means "not recorded" in real data

# discretize continuous columns so the network can use them (-inf / inf bins never produce NaN)
for col, cuts in {"age": [45, 60], "chol": [200, 240], "trestbps": [120, 140], "thalach": [120, 150]}.items():
    df[col] = pd.cut(df[col], [-float("inf")] + cuts + [float("inf")], labels=[0, 1, 2]).astype(int)
df = df.astype(int)

# structure: risk factors -> heart disease -> symptoms
model = DiscreteBayesianNetwork([("age", "target"), ("sex", "target"), ("chol", "target"), ("trestbps", "target"),
                                 ("target", "cp"), ("target", "exang"), ("target", "thalach")])
model.fit(df)                                            # learn probability tables (maximum likelihood)
infer = VariableElimination(model)

# diagnose patients
cases = {"older male, chest pain=0, exercise angina": {"age": 2, "sex": 1, "cp": 0, "exang": 1, "thalach": 0},
         "young female, no symptoms":                {"age": 0, "sex": 0, "cp": 2, "exang": 0, "thalach": 2}}
for name, evidence in cases.items():
    p = infer.query(["target"], evidence=evidence, show_progress=False)
    print(f"{name}: P(heart disease) = {p.values[1]:.2f}")