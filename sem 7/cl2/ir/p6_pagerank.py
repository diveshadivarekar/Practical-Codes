# 6. PageRank algorithm (power iteration) - checked against networkx
import numpy as np, networkx as nx

# web graph: page -> pages it links to
links = {"A": ["B", "C"], "B": ["C"], "C": ["A"], "D": ["C", "A"], "E": ["D", "C"]}
pages = sorted(links)
n, d = len(pages), 0.85                                   # d = damping factor
idx = {p: i for i, p in enumerate(pages)}

M = np.zeros((n, n))                                      # M[j][i] = 1/outlinks if i links to j
for p, outs in links.items():
    for o in outs:
        M[idx[o], idx[p]] = 1 / len(outs)

rank = np.ones(n) / n
for _ in range(100):                                      # PR = (1-d)/n + d * M * PR
    rank = (1 - d) / n + d * M @ rank

for p in sorted(pages, key=lambda p: -rank[idx[p]]):
    print(f"{p}: {rank[idx[p]]:.4f}")

# verify with the library version
print("networkx:", {k: round(v, 4) for k, v in nx.pagerank(nx.DiGraph([(p, o) for p, os in links.items() for o in os]), alpha=d).items()})

# For real web pages: use requests + BeautifulSoup to collect each page's <a href> links
# into the `links` dictionary above (see p7_web_crawler.py), then run the same code.
