import numpy as np
import math
import matplotlib.pyplot as plt

def least_squares_matrix(x, y, n):
    s = x.size
    A = np.zeros([n + 1, n + 1])
    b = np.zeros([n + 1])
    for i in range(n + 1):
        for k in range(s):
            b[i] += x[k] ** i * y[k]
        for j in range(n + 1):
            for k in range(s):
                A[i, j] += x[k] ** (i + j)
    return(np.linalg.solve(A, b))
