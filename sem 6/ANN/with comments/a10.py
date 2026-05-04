# Assignment 10: Hopfield Network storing 4 vectors

**Objective:** Implement a **Hopfield Network** that stores 4 bipolar patterns using Hebbian learning and can recall a stored pattern from a noisy/partial input.

## Requirements

Write a Python program to design a Hopfield Network which stores 4 vectors.

---
import numpy as np

# ---- Step Function ----
def sign(x):
    return np.where(x >= 0, 1, -1)

# ---- Define 4 Patterns (bipolar form: -1, 1) ----
patterns = np.array([
    [1, -1, 1, -1],
    [-1, 1, -1, 1],
    [1, 1, -1, -1],
    [-1, -1, 1, 1]
])

# ---- Training (Hebbian Learning) ----
n = patterns.shape[1]
W = np.zeros((n, n))

for p in patterns:
    W += np.outer(p, p)

# Remove self-connections
np.fill_diagonal(W, 0)

print("Weight Matrix:\n", W)

# ---- Testing (Recall) ----
test = np.array([1, -1, 1, 1])  # noisy version

print("\nInitial Input:", test)

# Update iteratively
for _ in range(5):
    test = sign(np.dot(W, test))
    print("Updated:", test)