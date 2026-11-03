# 4. E-mail spam filtering: TF-IDF + Naive Bayes
import pandas as pd
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.naive_bayes import MultinomialNB
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score, classification_report

df = pd.read_csv("data/spam.csv", encoding="latin-1")      # Kaggle SMS file is latin-1, not utf-8
df = df.rename(columns={"v1": "label", "v2": "message"})[["label", "message"]].dropna()   # works with v1/v2 or label/message
X_train, X_test, y_train, y_test = train_test_split(df.message, df.label, test_size=0.25, random_state=1)

vec = TfidfVectorizer(stop_words="english")               # text -> numbers
model = MultinomialNB().fit(vec.fit_transform(X_train), y_train)

pred = model.predict(vec.transform(X_test))
print("Accuracy:", accuracy_score(y_test, pred))
print(classification_report(y_test, pred))

for m in ["Congratulations you win free cash prize click now", "team meeting tomorrow please review the report"]:
    print(f"'{m}' ->", model.predict(vec.transform([m]))[0])