import numpy as np
from scipy.stats import multivariate_normal

mean1 = [2, 3]
cov1 = [[1, 0.5], [0.5, 1]]
mean2 = [6, 7]
cov2 = [[1, -0.3], [-0.3, 1]]
P1 = 0.5
P2 = 0.5

x = np.array([4, 5])

p_x_given_c1 = multivariate_normal.pdf(x, mean=mean1, cov=cov1)
p_x_given_c2 = multivariate_normal.pdf(x, mean=mean2, cov=cov2)

posterior1 = p_x_given_c1 * P1
posterior2 = p_x_given_c2 * P2

print("Posterior Probabilities:")
print("Class 1:", posterior1)
print("Class 2:", posterior2)

if posterior1 > posterior2:
    print("Classified as: Class 1")
else:
    print("Classified as: Class 2")