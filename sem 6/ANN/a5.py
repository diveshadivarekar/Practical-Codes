import numpy as np

# Sigmoid activation
def sigmoid(x):
    return 1 / (1 + np.exp(-x))

# Derivative of sigmoid
def sigmoid_derivative(x):
    return x * (1 - x)

# Input dataset (XOR)
X = np.array([[0,0],
              [0,1],
              [1,0],
              [1,1]])

# Output
y = np.array([[0],[1],[1],[0]])

# Initialize weights
np.random.seed(1)
W1 = np.random.rand(2, 2)   # input → hidden
W2 = np.random.rand(2, 1)   # hidden → output

# Training
epochs = 10000
lr = 0.5

for epoch in range(epochs):

    # ---- Forward Propagation ----
    hidden_input = np.dot(X, W1)
    hidden_output = sigmoid(hidden_input)

    final_input = np.dot(hidden_output, W2)
    final_output = sigmoid(final_input)

    # ---- Error ----
    error = y - final_output

    # ---- Backpropagation ----
    d_output = error * sigmoid_derivative(final_output)

    error_hidden = d_output.dot(W2.T)
    d_hidden = error_hidden * sigmoid_derivative(hidden_output)

    # ---- Update Weights ----
    W2 += hidden_output.T.dot(d_output) * lr
    W1 += X.T.dot(d_hidden) * lr

# Output
print("Final Output after Training:")
print(final_output)