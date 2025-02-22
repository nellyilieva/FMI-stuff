import math
import numpy as np
import matplotlib.pyplot as plt

nodes = np.array([0, 0.95, 1.75, 4.75, 5.9])
vals = np.array([0, 10.3, 0.5, 0.9, 1.2])

A = np.ones([5, 5])

for i in range(5):
    for j in range(1, 5):
        if j % 2 != 0:
            A[i, j] = np.cos((j // 2 + 1) * nodes[i])
        else:
            A[i, j] = np.sin(j / 2 * nodes[i])

sol = np.linalg.solve(A, vals)


def trig_poly(x):
    return sol[0] + sol[1] * np.cos(x) + sol[2] * np.sin(x) + sol[3] * np.cos(2 * x) + sol[4] * np.sin(2 * x)


def lagrange_poly(nodes, vals, x):
    result = 0.0
    n = nodes.size
    for i in range(n):
        l_i = vals[i]
        for j in range(n):
            if j != i:
                l_i *= (x - nodes[j]) / (nodes[i] - nodes[j])
        result += l_i
    return result


x_axis = np.linspace(0, 6, 300)
plt.plot(x_axis, trig_poly(x_axis), color="blue")
plt.plot(x_axis, lagrange_poly(nodes, vals, x_axis), color="red")
plt.scatter(nodes, vals)
plt.show()