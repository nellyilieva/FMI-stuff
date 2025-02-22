import math
import numpy as np
import matplotlib.pyplot as plt

nodes = np.array([0, 1.5, 3, 4, 6])
vals = np.array([0, 1, 1.5, 4, 2])
A = np.ones([5, 5])

nodes_changed = (2 * np.pi) / 8 * nodes

A = np.ones([5, 5])
for i in range (5):
    for j in range (1, 5):
        if j % 2 != 0:
            A[i, j] = np.cos((math.floor(j / 2) + 1) * nodes_changed[i])
        else:
            A[i, j] = np.sin(j / 2 * nodes_changed[i])


sol = np.linalg.solve(A, vals)

def poly(x):
    return sol[0] + sol[1] * np.cos(x) + sol[2] * np.sin(x) + sol[3] * np.cos(2 * x) + sol[4] * np.sin(2 * x)

x_axis = np.linspace(0, 4 * np.pi, 1000)
plt.plot(x_axis, poly(x_axis))
plt.scatter(nodes_changed, vals)
plt.show()
