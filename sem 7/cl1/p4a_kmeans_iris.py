# 4A. K-Means on Iris + elbow method
import pandas as pd, matplotlib.pyplot as plt
from sklearn.cluster import KMeans

X = pd.read_csv("data/Iris.csv").drop(columns="species")

# Elbow method
wcss = [KMeans(n_clusters=k, n_init=10, random_state=1).fit(X).inertia_ for k in range(1, 11)]
plt.plot(range(1, 11), wcss, "o-"); plt.xlabel("k"); plt.ylabel("WCSS"); plt.title("Elbow method"); plt.show()

# Elbow is at k=3
km = KMeans(n_clusters=3, n_init=10, random_state=1).fit(X)
plt.scatter(X.iloc[:, 2], X.iloc[:, 3], c=km.labels_)
plt.scatter(km.cluster_centers_[:, 2], km.cluster_centers_[:, 3], c="red", marker="X", s=200)
plt.xlabel("petal length"); plt.ylabel("petal width"); plt.title("K-Means (k=3)"); plt.show()
