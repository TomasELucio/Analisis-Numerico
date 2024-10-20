import numpy as np
import matplotlib.pyplot as plt

def regresion_lineal(x, y):
    n = len(x)
    sum_x = np.sum(x)
    sum_y = np.sum(y)
    sum_xy = np.sum(x * y)
    sum_x2 = np.sum(x * x)

    a1 = (n * sum_xy - sum_x * sum_y) / (n * sum_x2 - sum_x * sum_x)
    a0 = (sum_y - a1 * sum_x) / n
    return a0, a1

def regresion_lineal_exponencial(x, y):
    n = len(x)
    sum_x = np.sum(x)
    sum_y = np.sum(np.log(y))
    sum_xy = np.sum(x * np.log(y))
    sum_x2 = np.sum(x * x)

    a1 = (n * sum_xy - sum_x * sum_y) / (n * sum_x2 - sum_x * sum_x)
    a0 = (sum_y - a1 * sum_x) / n
    return a0, a1

def regresion_lineal_potencial(x, y):
    n = len(x)
    sum_x = np.sum(np.log10(x))
    sum_y = np.sum(np.log10(y))
    sum_xy = np.sum(np.log10(x) * np.log10(y))
    sum_x2 = np.sum(np.log10(x) * np.log10(x))

    a1 = (n * sum_xy - sum_x * sum_y) / (n * sum_x2 - sum_x * sum_x)
    a0 = (sum_y - a1 * sum_x) / n
    return a0, a1

def plot_regression(x, y, a0, a1, model_type):
    plt.scatter(x, y, color='blue', label='Data points')
    x_fit = np.linspace(min(x), max(x), 100)
    
    if model_type == 'lineal':
        y_fit = a0 + a1 * x_fit
        plt.plot(x_fit, y_fit, color='red', label=f'y = {a0:.2f} + {a1:.2f}x')
    elif model_type == 'exponencial':
        y_fit = np.exp(a0) * np.exp(a1 * x_fit)
        plt.plot(x_fit, y_fit, color='red', label=f'y = {np.exp(a0):.2f}e^({a1:.2f}x)')
    elif model_type == 'potencial':
        y_fit = 10**a0 * x_fit**a1
        plt.plot(x_fit, y_fit, color='red', label=f'y = {10**a0:.2f}x^{a1:.2f}')
    
    plt.xlabel('x')
    plt.ylabel('y')
    plt.legend()
    plt.title(f'Regression Model: {model_type.capitalize()}')
    plt.show()

def main():
    x = np.array([1, 2, 3, 4, 5])
    y = np.array([0.5, 1.7, 3.4, 5.7, 8.4])

    a0, a1 = 0.0, 0.0

    lineal = False
    exponencial = True
    potencial = False
    decrecimiento = False

    if lineal:
        a0, a1 = regresion_lineal(x, y)
        print(f"La ecuación de la recta es: y = {a0} + {a1}x")
        plot_regression(x, y, a0, a1, 'lineal')
    
    if exponencial:
        a0, a1 = regresion_lineal_exponencial(x, y)
        print(f"La ecuación del modelo exponencial es: y = {np.exp(a0)}e^({a1}x)")
        plot_regression(x, y, a0, a1, 'exponencial')
    
    if potencial:
        a0, a1 = regresion_lineal_potencial(x, y)
        print(f"La ecuación del modelo potencial es: y = {10**a0}x^{a1}")
        plot_regression(x, y, a0, a1, 'potencial')
    
    if decrecimiento:
        print(f"La ecuación de la recta es: y = {1/a0}(x/({a1*(1/a0)} + x))")

if __name__ == "__main__":
    main()