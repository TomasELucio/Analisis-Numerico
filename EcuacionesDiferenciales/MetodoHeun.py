import numpy as np
import matplotlib.pyplot as plt

def heun(f, t0, y0, t_final, h):
    """
    Método de Heun para resolver la ecuación diferencial y' = f(t, y)
    
    Parámetros:
    f       -- función que representa la ecuación diferencial y' = f(t, y)
    t0      -- valor inicial de t
    y0      -- valor inicial de y
    t_final -- valor final de t
    h       -- tamaño del paso

    Retorna:
    t_values -- array con los valores de t
    y_values -- array con los valores de y calculados en los puntos t
    """
    
    # Inicializar las listas para t y y
    t_values = np.arange(t0, t_final + h, h)
    y_values = np.zeros(len(t_values))
    
    # Condiciones iniciales
    y_values[0] = y0
    
    # Imprimir encabezado de la tabla
    print(f"{'Iteración':<10} {'t':<10} {'y (aproximado)':<20} {'y_pred (Euler)':<20}")
    print("-" * 60)
    
    # Imprimir valores iniciales
    print(f"{0:<10} {t0:<10.4f} {y0:<20.6f} {'-':<20}")
    
    # Aplicar el método de Heun
    for i in range(1, len(t_values)):
        t = t_values[i - 1]
        y = y_values[i - 1]
        
        # Pendiente en el inicio (Euler)
        f1 = f(t, y)
        
        # Predicción usando Euler
        y_pred = y + h * f1
        
        # Pendiente en el final del intervalo
        f2 = f(t + h, y_pred)
        
        # Promedio de las pendientes
        y_values[i] = y + (h / 2) * (f1 + f2)
        
        # Imprimir los valores de cada iteración
        print(f"{i:<10} {t_values[i]:<10.4f} {y_values[i]:<20.6f} {y_pred:<20.6f}")
    
    return t_values, y_values

# Definir la ecuación diferencial
# Ejemplo: y' = -2 * t * y
def f(x, y):
    return np.exp(0.8 * x) - 0.50 * y

# Parámetros iniciales
x0 = 0        # Tiempo inicial
y0 = 2        # Valor inicial de y
x_final = 4   # Tiempo final
h = 0.1       # Tamaño del paso

# Aplicar el método de Heun
t_values, y_values = heun(f, x0, y0, x_final, h)

# Graficar los resultados
plt.plot(t_values, y_values, label="Heun Method", color="green")
plt.xlabel("t")
plt.ylabel("y(t)")
plt.title("Método de Heun para y' = -2 * t * y")
plt.legend()
plt.grid(True)
plt.show()
