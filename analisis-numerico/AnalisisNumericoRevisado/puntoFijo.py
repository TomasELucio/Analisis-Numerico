import numpy as np
import matplotlib.pyplot as plt

error = 1e-5

def g(x):
    return np.exp(-x)

xi = 0.4

while(True):
    xn = g(xi)
    if abs(xn - xi) < error:
        print(f"La raíz es {xn}")
        break
    xi = xn
