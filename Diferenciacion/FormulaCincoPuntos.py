#falta corregir un toque 
import numpy as np
import sympy as sp

def diferencia_cinco_puntos_funcion(funcion, a, b, h):
    """
    Método de diferenciación numérica utilizando la fórmula de tres puntos para una función.
    
    :param funcion: Función a diferenciar.
    :param a: Extremo inferior del intervalo.
    :param b: Extremo superior del intervalo.
    :param h: Tamaño del paso.
    :return: Lista de valores de x y derivada aproximada en cada punto.
    """
    
    x_vals = np.arange(a, b + h, h)
    y_vals = [funcion(x) for x in x_vals]
    
    
    dy = diferencia_cinco_puntos(x_vals, y_vals,h)
    return x_vals, dy

def diferencia_cinco_puntos(x, y, h):
    """
    Método de diferenciación numérica utilizando la fórmula de cinco puntos hacia adelante, centrada y hacia atrás.
    
    :param x: Lista o array de valores de x.
    :param y: Lista o array de valores de la función evaluada en cada valor de x.
    :param h: Paso de la discretización.
    :return: Lista de valores de la derivada aproximada.
    """
    if len(x) != len(y):
        raise ValueError("Las longitudes de x e y deben ser iguales")
    
    n = len(x)
    dy = np.zeros(n)
    
    # Fórmula de cinco puntos hacia adelante para los primeros dos puntos
    dy[0] = (-25 * y[0] + 48 * y[1] - 36 * y[2] + 16 * y[3] - 3 * y[4]) / (12 * h)
    dy[1] = (-25 * y[1] + 48 * y[2] - 36 * y[3] + 16 * y[4] - 3 * y[5]) / (12 * h)

    # Fórmula de cinco puntos centrada para los puntos internos
    for i in range(2, n - 2):
        dy[i] = (y[i-2] - 8 * y[i-1] + 8 * y[i+1] - y[i+2]) / (12 * h)
    
    # Fórmula de cinco puntos hacia atrás para los últimos dos puntos
    dy[-2] = (3 * y[-6] - 16 * y[-5] + 36 * y[-4] - 48 * y[-3] + 25 * y[-2]) / (12 * h)
    dy[-1] = (3 * y[-5] - 16 * y[-4] + 36 * y[-3] - 48 * y[-2] + 25 * y[-1]) / (12 * h)
    
    return dy

opcion = input("Ingresa 1 o 2: ")
    
if(opcion == "1"):
    # Definir la función y su derivada
    x = sp.Symbol('x')
    funcion_expr = sp.exp(x) * sp.cos(x)  
    derivada_expr = sp.diff(funcion_expr, x)  
        
    # Convertir la función y la derivada en funciones evaluables
    funcion = sp.lambdify(x, funcion_expr, "numpy")
    derivada = sp.lambdify(x, derivada_expr, "numpy")

    # Definir el intervalo y el tamaño de paso
    a = 0       # Extremo inferior del intervalo
    b = 0.7       # Extremo superior del intervalo
    h = 0.1     # Tamaño del paso

    # Calcular la derivada numérica
    x_vals, derivadas_aprox = diferencia_cinco_puntos_funcion(funcion, a, b, h)

    # Calcular la derivada exacta y el error
    derivadas_exactas = [derivada(xi) for xi in x_vals]
    errores = [abs(d_aprox - d_exacta) for d_aprox, d_exacta in zip(derivadas_aprox, derivadas_exactas)]

        
elif(opcion == "2"):
    h = 0.1
    x_vals = [0 , 0.5 , 1 , 1.5 , 2]
    y_vals = [0, 0.4207 , 0.4546 , 0.0706 , -0.3784]
    if len(x_vals) != len(y_vals):
        raise ValueError("Las longitudes de x e y deben ser iguales")

    derivadas_aprox = diferencia_cinco_puntos(x_vals,y_vals,h)
        
    # Como no tenemos una función exacta, no se calculará el error
    derivadas_exactas = [None] * len(x_vals)
    errores = [None] * len(x_vals)
        
        
print("\nx\tDerivada Aproximada\tDerivada Exacta\t\tError")
for xi, dyi_aprox, dyi_exacta, error in zip(x_vals, derivadas_aprox, derivadas_exactas, errores):
    if dyi_exacta is not None and error is not None:
        print(f"{xi:.2f}\t{dyi_aprox:.5f}\t\t{dyi_exacta:.5f}\t\t{error:.6f}")
    else:
        print(f"{xi:.2f}\t{dyi_aprox:.5f}\t\t{'N/A':>8}\t\t{'N/A':>6}")