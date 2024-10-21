import numpy as np
import matplotlib.pyplot as plt

# Definir la función derivada dy/dx = f(x, y)
def f(x, y):
    return np.exp(0.8 * x) - 0.50 * y

# Método de Runge-Kutta de segundo orden
def runge_kutta_2(f, x0, y0, h, n):
    x = np.zeros(n+1)
    y = np.zeros(n+1)
    
    # Condiciones iniciales
    x[0] = x0
    y[0] = y0
    
    # Iterar sobre el número de pasos
    print(f"{'i':>3} {'x':>10} {'y':>10} {'k1':>10} {'k2':>10}")  # Encabezado de la tabla
    for i in range(0, n+1):
        k1 = f(x[i-1], y[i-1])
        k2 = f(x[i-1] + h, y[i-1] + h * k1)
        
        y[i] = y[i-1] + (h/2) * (k1 + k2)
        x[i] = x[i-1] + h
        
        # Imprimir valores de cada iteración en forma de tabla
        print(f"{i:3d} {x[i-1]:10.5f} {y[i-1]:10.5f} {k1:10.5f} {k2:10.5f}")
    
    return x, y

# Parámetros iniciales
x0 = 0   # valor inicial de x
y0 = 2   # valor inicial de y
h = 0.1  # tamaño del paso
n = int((4 - x0) / h)  # número de pasos, ahora asegurado que es entero

# Ejecutar el método
x_vals, y_vals = runge_kutta_2(f, x0, y0, h, n)

# Graficar la solución
plt.plot(x_vals, y_vals, label='Runge-Kutta 2do orden')
plt.xlabel('x')
plt.ylabel('y')
plt.title('Solución usando Runge-Kutta de 2do orden')
plt.legend()
plt.grid(True)
plt.show()
