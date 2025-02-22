import math
import numpy as np
import matplotlib.pyplot as plt

nodes = np.array([0, 1.5, 3, 4, 6])
vals = np.array([0, 1, 1.5, 4, 2])
A = np.ones([5, 5])

for i in range(5):
    for j in range(1, 5):
        if j % 2 != 0:
            A[i, j] = np.cos((math.floor(j / 2) + 1) * nodes[i])
        else:
            A[i, j] = np.sin(j / 2 * nodes[i])

sol = np.linalg.solve(A, vals)


def trig_poly_1(x):
    return sol[0] + sol[1] * np.cos(x) + sol[2] * np.sin(x) + sol[3] * np.cos(2 * x) + sol[4] * np.sin(2 * x)


x_axis = np.linspace(0, 4 * np.pi, 1000)
plt.plot(x_axis, trig_poly_1(x_axis))
plt.scatter(nodes, vals)
plt.show()
