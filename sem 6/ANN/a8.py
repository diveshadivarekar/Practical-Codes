import numpy as np

# Binary input patterns
patterns = np.array([
    [1, 1, 0, 0],
    [1, 1, 0, 1],
    [0, 0, 1, 1],
    [0, 1, 1, 1]
])

# Parameters
num_features = patterns.shape[1]
max_clusters = 5
rho = 0.6   # vigilance parameter

# Initialize weights
W = np.ones((max_clusters, num_features))   # top-down weights
T = np.ones((max_clusters, num_features))   # bottom-up weights

clusters = [-1] * len(patterns)

def match_score(p, w):
    return np.sum(p * w) / (np.sum(p) + 1e-8)

for i, p in enumerate(patterns):
    for j in range(max_clusters):
        score = match_score(p, W[j])

        if score >= rho:
            clusters[i] = j
            
            # Update weights (learning)
            W[j] = W[j] * p
            T[j] = W[j] / (0.5 + np.sum(W[j]))
            break

# Output
print("Pattern -> Cluster Assignment")
for i, c in enumerate(clusters):
    print(patterns[i], "-> Cluster", c)