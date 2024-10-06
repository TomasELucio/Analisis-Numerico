import numpy as np
import sympy as sp

def diferencia_tres_puntos_funcion(funcion, a, b, h):
    """
    Método de diferenciación numérica utilizando la fórmula de tres puntos para una función.
    
    :param funcion: Función a diferenciar.
    :param a: Extremo inferior del intervalo.
    :param b: Extremo superior del intervalo.
    :param h: Tamaño del paso.
    :return: Lista de valores de x y derivada aproximada en cada punto.
    """
    # Definir los puntos
    x_vals = np.arange(a, b + h, h)
    y_vals = [funcion(x) for x in x_vals]
    
    # Aplicar el método de tres puntos
    dy = diferencia_tres_puntos(x_vals, y_vals)
    return x_vals, dy

def diferencia_tres_puntos(x, y):
    """
    Método de diferenciación numérica utilizando la fórmula de tres puntos hacia adelante, hacia atrás y centrada.
    
    :param x: Lista o array de valores de x.
    :param y: Lista o array de valores de la función evaluada en cada valor de x.
    :return: Lista de valores de la derivada aproximada.
    """
    # Verificar que la longitud de x y y sea igual
    if len(x) != len(y):
        raise ValueError("Las longitudes de x e y deben ser iguales")
    
    # Longitud de los puntos
    n = len(x)
    h = x[1] - x[0]  # Se asume que h es constante
    dy = np.zeros(n)
    
    # Aplicar la fórmula de tres puntos hacia adelante para el primer punto
    dy[0] = (-3 * y[0] + 4 * y[1] - y[2]) / (2 * h)

    # Aplicar la fórmula de tres puntos centrada para los puntos internos
    for i in range(1, n - 1):
        dy[i] = (y[i + 1] - y[i - 1]) / (2 * h)
    
    # Aplicar la fórmula de tres puntos hacia atrás para el último punto
    dy[-1] = (y[-3] - 4 * y[-2] + 3 * y[-1]) / (2 * h)
    
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
    x_vals, derivadas_aprox = diferencia_tres_puntos_funcion(funcion, a, b, h)

    # Calcular la derivada exacta y el error
    derivadas_exactas = [derivada(xi) for xi in x_vals]
    errores = [abs(d_aprox - d_exacta) for d_aprox, d_exacta in zip(derivadas_aprox, derivadas_exactas)]

        
elif(opcion == "2"):
    x_vals = [0 , 0.5 , 1 , 1.5 , 2]
    y_vals = [0, 0.4207 , 0.4546 , 0.0706 , -0.3784]
    if len(x_vals) != len(y_vals):
        raise ValueError("Las longitudes de x e y deben ser iguales")

    derivadas_aprox = diferencia_tres_puntos(x_vals,y_vals)
        
    # Como no tenemos una función exacta, no se calculará el error
    derivadas_exactas = [None] * len(x_vals)
    errores = [None] * len(x_vals)
        
        
print("\nx\tDerivada Aproximada\tDerivada Exacta\t\tError")
for xi, dyi_aprox, dyi_exacta, error in zip(x_vals, derivadas_aprox, derivadas_exactas, errores):
    if dyi_exacta is not None and error is not None:
        print(f"{xi:.2f}\t{dyi_aprox:.5f}\t\t{dyi_exacta:.5f}\t\t{error:.6f}")
    else:
        print(f"{xi:.2f}\t{dyi_aprox:.5f}\t\t{'N/A':>8}\t\t{'N/A':>6}")