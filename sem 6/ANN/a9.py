import numpy as np

# Sigmoid activation
def sigmoid(x):
    return 1 / (1 + np.exp(-x))

# Derivative of sigmoid
def sigmoid_derivative(x):
    return x * (1 - x)

# Sample dataset (XOR problem)
X = np.array([[0,0],
              [0,1],
              [1,0],
              [1,1]])

y = np.array([[0],
              [1],
              [1],
              [0]])

# Initialize weights and bias
np.random.seed(0)
W1 = np.random.rand(2, 3)   # input → hidden (3 neurons)
b1 = np.zeros((1, 3))

W2 = np.random.rand(3, 1)   # hidden → output
b2 = np.zeros((1, 1))

lr = 0.5
epochs = 10000

# Training
for epoch in range(epochs):

    # ---- Forward Propagation ----
    Z1 = np.dot(X, W1) + b1
    A1 = sigmoid(Z1)

    Z2 = np.dot(A1, W2) + b2
    A2 = sigmoid(Z2)

    # ---- Error ----
    error = y - A2

    # ---- Backpropagation ----
    dA2 = error * sigmoid_derivative(A2)

    dW2 = np.dot(A1.T, dA2)
    db2 = np.sum(dA2, axis=0, keepdims=True)

    dA1 = np.dot(dA2, W2.T)
    dW1 = np.dot(X.T, dA1 * sigmoid_derivative(A1))
    db1 = np.sum(dA1 * sigmoid_derivative(A1), axis=0, keepdims=True)

    # ---- Update ----
    W2 += lr * dW2
    b2 += lr * db2
    W1 += lr * dW1
    b1 += lr * db1

# ---- Output ----
print("Final Output:")
print(A2)

# Binary result
print("\nBinary Output:")
print((A2 > 0.5).astype(int))