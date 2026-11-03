# 2. Document retrieval using an inverted index (with AND search)
import re, glob, os
from collections import defaultdict

docs = {os.path.basename(f)[:-4]: open(f).read() for f in sorted(glob.glob("data/docs/*.txt"))}

index = defaultdict(set)                         # word -> set of documents containing it
for name, text in docs.items():
    for word in re.findall(r"[a-z]+", text.lower()):
        index[word].add(name)

print("Index sample:", {w: sorted(index[w]) for w in ["documents", "web", "links"]})

def search(query):                               # documents that contain ALL query words
    sets = [index.get(w, set()) for w in re.findall(r"[a-z]+", query.lower())]
    return sorted(set.intersection(*sets)) if sets else []

for q in ["documents", "web pages", "spam filters"]:
    print(f"Query '{q}' ->", search(q))
