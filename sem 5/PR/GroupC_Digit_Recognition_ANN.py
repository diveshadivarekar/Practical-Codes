from sklearn import datasets
from sklearn.model_selection import train_test_split
from sklearn.neural_network import MLPClassifier
from sklearn.metrics import accuracy_score

digits = datasets.load_digits()
X_train, X_test, y_train, y_test = train_test_split(digits.data, digits.target, test_size=0.2)

mlp = MLPClassifier(hidden_layer_sizes=(64,), activation='relu', solver='adam', max_iter=500)
mlp.fit(X_train, y_train)

predictions = mlp.predict(X_test)
print("Neural Net Accuracy:", accuracy_score(y_test, predictions))