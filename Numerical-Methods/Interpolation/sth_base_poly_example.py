import math
import numpy as np
import matplotlib.pyplot as plt


nodes = np.array([0, 2, 4, 6, 8])
vals = np.array([0.1, 0.009, 0.0011, 0.00003, 0.0000012])

A = np.zeros([5, 5])

for i in range(5):
    for j in range(5):
        A[i, j] = 1 / (1 + j + nodes[i])

sol = np.linalg.solve(A, vals)


def poly(x):
    polynom = 0
    for i in range(5):
        polynom += sol[i] * 1 / (1 + i + x)
    return polynom


x_axis = np.linspace(0, 8, 100)
plt.plot(x_axis, poly(x_axis))
plt.scatter(nodes, vals)
plt.show()
