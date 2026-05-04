# Assignment 4: Perceptron learning law with decision regions (graphical)

**Objective:** Implement the **Perceptron learning law** for the OR gate and visualise the learned **decision boundary** as a 2D colour-filled region.

## Requirements

With a suitable example demonstrate the perceptron learning law with its decision regions using Python. Give the output in graphical form.

---
import numpy as np
import matplotlib.pyplot as plt

# AND gate dataset
X = np.array([[0,0],[0,1],[1,0],[1,1]])
y = np.array([0,0,0,1])

# Initialize
w = np.zeros(2)
b = 0
lr = 0.1

def step(x):
    return 1 if x >= 0 else 0

# Training
for epoch in range(10):
    for i in range(len(X)):
        net = np.dot(w, X[i]) + b
        pred = step(net)
        error = y[i] - pred
        
        # update rule
        w += lr * error * X[i]
        b += lr * error

print("Weights:", w)
print("Bias:", b)

# Plot decision boundary
x_vals = np.linspace(-0.5, 1.5, 100)
y_vals = -(w[0]*x_vals + b) / w[1]

plt.plot(x_vals, y_vals, label="Decision Boundary")

# Plot points
for i in range(len(X)):
    if y[i] == 0:
        plt.scatter(X[i][0], X[i][1], marker='o', label="Class 0" if i==0 else "")
    else:
        plt.scatter(X[i][0], X[i][1], marker='x', label="Class 1")

plt.xlabel("x1")
plt.ylabel("x2")
plt.title("Perceptron Decision Region (AND Gate)")
plt.legend()
plt.grid()
plt.show()