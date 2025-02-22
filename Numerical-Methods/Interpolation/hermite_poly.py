import math
import numpy as np


def divided_diff_extended(nodes, values, l, r):
    if nodes[l] == nodes[r]:
        return values[np.argmax(nodes == nodes[l]) + r - l] / math.factorial(r-l)
    return ((divided_diff_extended(nodes, values, l+1, r) - divided_diff_extended(nodes, values, l, r - 1))
            / (nodes[r] - nodes[l]))


def hermite(nodes, values, x):
    res = 0
    mult = 1
    for i in range(len(nodes)):
        res += divided_diff_extended(nodes, values, 0, i) * mult
        mult *= x - nodes[i]
    return res
