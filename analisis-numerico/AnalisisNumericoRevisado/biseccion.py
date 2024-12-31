import numpy as np
import matplotlib.pyplot as plt

paso = 0.01
a = 0 # Límite inferior
b = 2    # Límite superior
error = 1e-5

def f(x):
    return np.exp(-x) - x


def buscaIntervalos(a, b, paso):
    subintervalos = []
    puntos = []
    x = a
    while x <= b:
        puntos.append(x)
        x += paso
    
    for i in range(len(puntos) - 1):
        contieneRaiz = f(puntos[i]) * f(puntos[i + 1]) < 0
        subintervalos.append((puntos[i], puntos[i + 1], contieneRaiz,f(puntos[i]) * f(puntos[i + 1])))
            
    return subintervalos

def biseccion(a, b, error):
    while abs(b - a) > error:
        c = (a + b) / 2
        if f(a) * f(c) < 0:
            b = c
        else:
            a = c
            
    return c

intervalos = buscaIntervalos(a, b, paso)

# Crear una tabla para los intervalos y raíces
print("\nTabla de Intervalos y Raíces")
print("Intervalo            Raíz           Producto     ¿Contiene Raíz?")
print("--------------------------------------------------------------")
for (a_i, b_i, contieneRaiz, producto) in intervalos:
    signo = '+' if producto > 0 else '-' if producto < 0 else '0'
    if contieneRaiz:
        raiz = biseccion(a_i, b_i, error)
        print(f"[{a_i:.2f}, {b_i:.2f}]   {raiz:.6f}       {producto:.6f}       {signo}")
    else:
        print(f"[{a_i:.2f}, {b_i:.2f}]   N/A             {producto:.6f}       {signo}")

# Graficar la función
x_vals = np.linspace(a, b, 500)
y_vals = f(x_vals)

plt.figure(figsize=(10, 6))
plt.plot(x_vals, y_vals, label="f(x)", color="blue")
plt.axhline(0, color="black", linestyle="--", linewidth=0.8)
plt.title("Gráfico de la función f(x)")
plt.xlabel("x")
plt.ylabel("f(x)")
plt.grid(True)
plt.legend()
plt.show()