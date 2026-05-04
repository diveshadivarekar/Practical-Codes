# Assignment 3: Perceptron Neural Network to recognise even and odd numbers (ASCII 0-9)

**Objective:** Train a **Perceptron** to classify digits 0–9 (given as 6-bit ASCII binary) as even (1) or odd (0) using the perceptron learning rule.

## Requirements

Write a Python Program using Perceptron Neural Network to recognise even and odd numbers. Given numbers are in ASCII form 0 to 9.

---
import numpy as np

# Convert number (0–9) to 8-bit ASCII binary
def to_ascii_binary(n):
    ascii_val = ord(str(n))
    return np.array([int(x) for x in format(ascii_val, '08b')])

# Training data
X = np.array([to_ascii_binary(i) for i in range(10)])
y = np.array([1 if i % 2 == 0 else 0 for i in range(10)])  # 1=Even, 0=Odd

# Initialize weights and bias
w = np.zeros(8)
b = 0
lr = 0.1

# Step activation function
def step(x):
    return 1 if x >= 0 else 0

# Training
for epoch in range(20):
    for i in range(len(X)):
        net = np.dot(w, X[i]) + b
        pred = step(net)
        error = y[i] - pred
        
        # Update rule
        w += lr * error * X[i]
        b += lr * error

# Testing
print("Number | Prediction")
for i in range(10):
    x = to_ascii_binary(i)
    net = np.dot(w, x) + b
    pred = step(net)
    print(i, "     |", "Even" if pred == 1 else "Odd")