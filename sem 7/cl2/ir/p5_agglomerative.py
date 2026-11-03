# 5. Agglomerative hierarchical clustering on Iris (built into scikit-learn)
import matplotlib.pyplot as plt
from sklearn.datasets import load_iris
from sklearn.cluster import AgglomerativeClustering
from sklearn.metrics import adjusted_rand_score
from scipy.cluster.hierarchy import dendrogram, linkage

X, y = load_iris(return_X_y=True)

# dendrogram (shows how clusters merge)
dendrogram(linkage(X, method="ward"), truncate_mode="lastp", p=20)
plt.title("Dendrogram (Ward linkage)"); plt.xlabel("samples"); plt.ylabel("distance"); plt.show()

# cut the tree into 3 clusters
labels = AgglomerativeClustering(n_clusters=3, linkage="ward").fit_predict(X)
print("Agreement with real species (ARI):", round(adjusted_rand_score(y, labels), 3))

plt.scatter(X[:, 2], X[:, 3], c=labels); plt.xlabel("petal length"); plt.ylabel("petal width")
plt.title("Agglomerative clusters (k=3)"); plt.show()
