# bayes_gaussian.py
import numpy as np
from sklearn.datasets import make_classification
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score, confusion_matrix

class GaussianBayes:
    def __init__(self, priors=None, var_smoothing=1e-6):
        self.priors = priors
        self.var_smoothing = var_smoothing

    def fit(self, X, y):
        self.classes_ = np.unique(y)
        n_features = X.shape[1]
        self.means_ = {}
        self.vars_ = {}
        self.priors_ = {}
        for c in self.classes_:
            Xc = X[y == c]
            self.means_[c] = Xc.mean(axis=0)
            # unbiased sample variance
            self.vars_[c] = Xc.var(axis=0) + self.var_smoothing
            self.priors_[c] = Xc.shape[0] / X.shape[0] if self.priors is None else self.priors.get(c, 1e-9)

    def _gaussian_logpdf(self, x, mean, var):
        # log of multivariate gaussian assuming diagonal covariance
        return -0.5 * np.sum(np.log(2 * np.pi * var) + ((x - mean) ** 2) / var, axis=1)

    def predict(self, X):
        log_posteriors = []
        for c in self.classes_:
            log_like = self._gaussian_logpdf(X, self.means_[c], self.vars_[c])
            log_prior = np.log(self.priors_[c])
            log_posteriors.append(log_like + log_prior)
        log_posteriors = np.vstack(log_posteriors).T  # shape (n_samples, n_classes)
        idx = np.argmax(log_posteriors, axis=1)
        return self.classes_[idx]

# Demo using synthetic data
if __name__ == "__main__":
    X, y = make_classification(n_samples=1000, n_features=4, n_informative=3, n_redundant=0, n_classes=2, random_state=0)
    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=1)
    clf = GaussianBayes()
    clf.fit(X_train, y_train)
    preds = clf.predict(X_test)
    print("Accuracy:", accuracy_score(y_test, preds))
    print("Confusion Matrix:\n", confusion_matrix(y_test, preds))
