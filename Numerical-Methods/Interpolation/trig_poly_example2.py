import math
import numpy as np
import matplotlib.pyplot as plt

nodes_with_aug = np.arange(0, 12 * 30, 30)
nodes = np.delete(nodes_with_aug, 7)
vals = np.array([45.9, 78.2, 123.5, 172.6, 223.5, 255.3, 286.0, 183.9, 116.2, 57.8, 37.7])
nodes_change = (2 * np.pi) / 365 * nodes

A = np.ones([11, 11])

for i in range(11):
    for j in range(1, 11):
        if j % 2 != 0:
            A[i, j] = np.cos((math.floor(j / 2) + 1) * nodes_change[i])
        else:
            A[i, j] = np.sin(j / 2 * nodes_change[i])

sol = np.linalg.solve(A, vals)


def poly(x):
    polynom = sol[0]
    for i in range(1, sol.size):
        if i % 2 != 0:
            polynom += sol[i] * np.cos((math.floor(i / 2) + 1) * x)
        else:
            polynom += sol[i] * np.sin(i / 2 * x)
    return polynom


x_axis = np.linspace(0, 2 * np.pi, 1000)
plt.plot(x_axis, poly(x_axis))
plt.scatter(nodes_change, vals)
plt.show()
