# Assignment 11: Train a Neural Network with TensorFlow and evaluate logistic regression

**Objective:** Use **TensorFlow/Keras** to build and compare two models on the Iris dataset:
1. A 2-layer **Neural Network** (Dense + ReLU)
2. A single-layer **Logistic Regression** model

## Requirements

How to train a Neural Network with TensorFlow and perform evaluation of logistic regression using TensorFlow.

---
import tensorflow as tf
from tensorflow.keras import layers, models
from sklearn.datasets import load_iris
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler

# Load dataset
data = load_iris()
X, y = data.data, data.target

# Preprocess
scaler = StandardScaler()
X = scaler.fit_transform(X)

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2)

# Build model
model = models.Sequential([
    layers.Dense(16, activation='relu', input_shape=(4,)),
    layers.Dense(8, activation='relu'),
    layers.Dense(3, activation='softmax')  # multi-class
])

# Compile
model.compile(optimizer='adam',
              loss='sparse_categorical_crossentropy',
              metrics=['accuracy'])

# Train
model.fit(X_train, y_train, epochs=50, verbose=0)

# Evaluate
loss, acc = model.evaluate(X_test, y_test)
print("Accuracy:", acc)