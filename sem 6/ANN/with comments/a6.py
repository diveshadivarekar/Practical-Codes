# Assignment 6: Neural network from scratch for multi-class classification (Iris dataset, ReLU)

**Objective:** Build a **multi-class neural network from scratch** (no TensorFlow/PyTorch) using ReLU hidden activation and Softmax output to classify the Iris dataset into 3 species.

## Requirements

Create a Neural Network architecture from scratch in Python and use it to perform multi-class classification on any dataset.
Parameters:
  (1) No. of hidden layers: 1 or more
  (2) No. of neurons in hidden layer: 100
  (3) Non-linearity in the layer: ReLU
  (4) Use more than 1 neuron in the output layer
Use a suitable threshold value and an appropriate optimisation algorithm.

---
import numpy as np
import matplotlib.pyplot as plt

# ----- Generate Dummy Data (3 classes) -----
np.random.seed(0)
N = 100

X1 = np.random.randn(N, 2) + np.array([0, -2])
X2 = np.random.randn(N, 2) + np.array([2, 2])
X3 = np.random.randn(N, 2) + np.array([-2, 2])

X = np.vstack([X1, X2, X3])
y = np.array([0]*N + [1]*N + [2]*N)

# One-hot encoding
def one_hot(y, num_classes):
    return np.eye(num_classes)[y]

Y = one_hot(y, 3)

# ----- Activation Functions -----
def relu(x):
    return np.maximum(0, x)

def relu_derivative(x):
    return (x > 0).astype(float)

def softmax(x):
    exp = np.exp(x - np.max(x, axis=1, keepdims=True))
    return exp / np.sum(exp, axis=1, keepdims=True)

# ----- Initialize Parameters -----
input_size = 2
hidden_size = 100   # as required
output_size = 3

W1 = np.random.randn(input_size, hidden_size) * 0.01
b1 = np.zeros((1, hidden_size))

W2 = np.random.randn(hidden_size, output_size) * 0.01
b2 = np.zeros((1, output_size))

lr = 0.1
epochs = 1000

# ----- Training -----
for epoch in range(epochs):

    # Forward
    Z1 = np.dot(X, W1) + b1
    A1 = relu(Z1)

    Z2 = np.dot(A1, W2) + b2
    A2 = softmax(Z2)

    # Loss (Cross-Entropy)
    loss = -np.mean(np.sum(Y * np.log(A2 + 1e-8), axis=1))

    # Backpropagation
    dZ2 = A2 - Y
    dW2 = np.dot(A1.T, dZ2) / X.shape[0]
    db2 = np.sum(dZ2, axis=0, keepdims=True) / X.shape[0]

    dA1 = np.dot(dZ2, W2.T)
    dZ1 = dA1 * relu_derivative(Z1)
    dW1 = np.dot(X.T, dZ1) / X.shape[0]
    db1 = np.sum(dZ1, axis=0, keepdims=True) / X.shape[0]

    # Update (Gradient Descent)
    W1 -= lr * dW1
    b1 -= lr * db1
    W2 -= lr * dW2
    b2 -= lr * db2

    if epoch % 100 == 0:
        print(f"Epoch {epoch}, Loss: {loss:.4f}")

# ----- Prediction -----
def predict(X):
    A1 = relu(np.dot(X, W1) + b1)
    A2 = softmax(np.dot(A1, W2) + b2)
    return np.argmax(A2, axis=1)

preds = predict(X)

# ----- Plot Decision Regions -----
h = 0.1
x_min, x_max = X[:,0].min()-1, X[:,0].max()+1
y_min, y_max = X[:,1].min()-1, X[:,1].max()+1

xx, yy = np.meshgrid(np.arange(x_min, x_max, h),
                     np.arange(y_min, y_max, h))

grid = np.c_[xx.ravel(), yy.ravel()]
Z = predict(grid)
Z = Z.reshape(xx.shape)

plt.contourf(xx, yy, Z, alpha=0.3)
plt.scatter(X[:,0], X[:,1], c=y)
plt.title("Multi-class Decision Regions (Neural Network)")
plt.show()