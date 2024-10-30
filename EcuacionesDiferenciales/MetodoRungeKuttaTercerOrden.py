def runge_kutta_3rd_order(f, x0, y0, h, n):
    """
    Método de Runge-Kutta de tercer orden para resolver ecuaciones diferenciales ordinarias.
    
    Parámetros:
    - f: función que define la ecuación diferencial (y' = f(x, y))
    - x0: valor inicial de x
    - y0: valor inicial de y
    - h: tamaño del paso
    - n: número de pasos a realizar
    
    Retorna:
    - Lista de tuplas (x, y) con los valores aproximados de la solución.
    """
    results = [(x0, y0)]
    x, y = x0, y0
    
    for _ in range(n):
        k1 = h * f(x, y)
        k2 = h * f(x + h/2, y + k1/2)
        k3 = h * f(x + h, y - k1 + 2 * k2)
        
        # Actualizamos el valor de y usando el promedio de las pendientes
        y = y + (k1 + 4 * k2 + k3) / 6
        x = x + h
        
        results.append((x, y))
    
    return results

# Ejemplo de uso:
# Definimos la función f(x, y) = y' = f(x, y)
def f(x, y):
    return x + y  # Cambia esta función según el problema específico

# Parámetros iniciales
x0 = 0      # Valor inicial de x
y0 = 1      # Valor inicial de y
h = 0.1     # Tamaño del paso
n = 10      # Número de pasos

# Ejecutamos el método de Runge-Kutta de tercer orden
solucion = runge_kutta_3rd_order(f, x0, y0, h, n)

# Imprimimos los resultados
for (x, y) in solucion:
    print(f"x: {x:.4f}, y: {y:.4f}")
