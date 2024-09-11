#include <iostream>
#include <cmath>
#include <iomanip>
#include <functional>

using namespace std;

// Función recursiva para ejecutar el método de punto fijo
void punto_fijo_recursivo(function<double(double)> g, double Xi, double tol, int iteracion, int max_iter) {
    double gx = g(Xi);
    double error = fabs(gx - Xi);

    // Imprimir los resultados de la iteración actual
    cout << setw(10) << iteracion
         << setw(15) << Xi 
         << setw(15) << gx 
         << setw(15) << error << endl;

    // Condición de parada por tolerancia o máximo de iteraciones
    if (error < tol || iteracion >= max_iter) {
        cout << "------------------------------------------\n";
        cout << "Última iteración:\n";
        cout << setw(10) << iteracion
             << setw(15) << Xi 
             << setw(15) << gx 
             << setw(15) << error << endl;
        cout << "------------------------------------------\n";
        return;
    }

    punto_fijo_recursivo(g, gx, tol, iteracion + 1, max_iter);
}

int main() {
    // Definir la función directamente en el código
    function<double(double)> g = [](double x) {
        return (23.330 - 88.090 * x * x + 41.600 * x * x * x - 8.680 * x * x * x * x + 0.658 * x * x * x * x * x) / 79.350;
    };

    // Definir el valor inicial, la tolerancia y el número máximo de iteraciones directamente en el código
    double x0 = 2.5;    // Valor inicial
    double tol = 1e-3;  // Tolerancia
    int max_iter = 100; // Número máximo de iteraciones

    // Imprimir la cabecera de la tabla
    cout << setw(10) << "Iteración" 
         << setw(15) << "Xi" 
         << setw(15) << "g(Xi)" 
         << setw(15) << "Error" << endl;

    // Ejecutar el método de punto fijo recursivo
    punto_fijo_recursivo(g, x0, tol, 1, max_iter);

    return 0;
}
