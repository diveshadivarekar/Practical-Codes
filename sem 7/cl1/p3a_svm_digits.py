# 3A. SVM on handwritten digits (0-9) - dataset is built into scikit-learn
import matplotlib.pyplot as plt
from sklearn.datasets import load_digits
from sklearn.svm import SVC
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score, classification_report

digits = load_digits()
X_train, X_test, y_train, y_test = train_test_split(digits.data, digits.target, test_size=0.2, random_state=1)

svm = SVC(kernel="rbf", gamma=0.001).fit(X_train, y_train)
pred = svm.predict(X_test)
print("Accuracy:", accuracy_score(y_test, pred))
print(classification_report(y_test, pred))

# show a few predictions
for i in range(5):
    plt.subplot(1, 5, i + 1)
    plt.imshow(X_test[i].reshape(8, 8), cmap="gray"); plt.title(f"Pred {pred[i]}"); plt.axis("off")
plt.show()
