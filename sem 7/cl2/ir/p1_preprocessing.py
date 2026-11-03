# 1. Text pre-processing: lowercase -> tokenize -> stop-word removal -> stemming
import re
from nltk.stem import PorterStemmer                              # works offline, no download needed
from sklearn.feature_extraction.text import ENGLISH_STOP_WORDS   # built-in stop-word list

text = open("data/docs/doc3.txt").read()                         # or any text you like
print("Original :", text)

tokens = re.findall(r"[a-z]+", text.lower())                     # lowercase + remove punctuation + tokenize
print("Tokens   :", tokens)

filtered = [w for w in tokens if w not in ENGLISH_STOP_WORDS]    # stop-word removal
print("No stop  :", filtered)

stemmer = PorterStemmer()
stemmed = [stemmer.stem(w) for w in filtered]                    # stemming
print("Stemmed  :", stemmed)
