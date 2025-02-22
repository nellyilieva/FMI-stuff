import math
import numpy as np
import matplotlib.pyplot as plt

nodes = np.array([0, 0.03, 0.07, 0.15, 0.21, 0.27])
vals = np.array([1, 1.06, 2.09, 22.1, 99.78, 328.602])
A = np.zeros([6, 6])

for i in range(6):
    for j in range(6):
        A[i, j] = np.e ** (j * nodes[i])

sol = np.linalg.solve(A, vals)


def poly(x):
    polynom = 0
    for i in range(6):
        polynom += sol[i] * np.exp(x * i)
    return polynom


x_axis = np.linspace(0, 0.27, 100)
plt.plot(x_axis, poly(x_axis))
plt.scatter(nodes, vals)
plt.show()
