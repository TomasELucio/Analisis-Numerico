import numpy as np
import pandas as pd

def punto_fijo(g, x0, tol=1e-4, max_iter=100):
    # Inicializar valores
    x_prev = x0
    tabla = []
    
    for i in range(max_iter):
        # Calcular la siguiente aproximación
        x_next = g(x_prev)
        error = abs(x_next - x_prev)
        
        # Guardar los valores en la tabla
        tabla.append([i+1, x_prev, x_next, error])
        
        # Verificar si el error es menor que la tolerancia
        if error < tol:
            break
        
        x_prev = x_next
    
    # Convertir la lista en un DataFrame para una mejor presentación
    tabla_df = pd.DataFrame(tabla, columns=["Iteración", "x_prev", "x_next", "Error"])
    
    return tabla_df

# Definir la función g(x) tal que x = g(x)
def g(x):
    return np.exp(-x)

# Valor inicial
x0 = 0.4

# Ejecutar el método de punto fijo
tabla_resultados = punto_fijo(g, x0)

# Mostrar la tabla de resultados
print(tabla_resultados)
