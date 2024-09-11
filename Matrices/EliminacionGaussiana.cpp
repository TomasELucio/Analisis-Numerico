#include <iostream>   // Biblioteca para entrada y salida de datos
#include <vector>     // Biblioteca para manejar vectores (arreglos dinámicos)
#include <iomanip>    // Biblioteca para manipular la salida de datos (formato, precisión)

using namespace std;

// Función que implementa el método de eliminación gaussiana
void eliminacionGaussiana(vector<vector<double>>& matriz, vector<double>& resultados, int n) {
    // Fase de eliminación para convertir la matriz en triangular superior
    for (int i = 0; i < n; i++) {
        // Aseguramos que el elemento en la diagonal principal sea 1
        double diag = matriz[i][i];  // Guardamos el valor diagonal actual
        for (int j = 0; j < n; j++) {
            matriz[i][j] /= diag;  // Dividimos toda la fila i por el elemento diagonal
        }
        resultados[i] /= diag;  // Ajustamos el término independiente

        // Hacemos ceros debajo de la diagonal principal
        for (int k = i + 1; k < n; k++) {
            double factor = matriz[k][i];  // Factor por el cual multiplicaremos la fila para restarla
            for (int j = 0; j < n; j++) {
                matriz[k][j] -= factor * matriz[i][j];  // Restamos la fila i multiplicada por el factor
            }
            resultados[k] -= factor * resultados[i];  // Ajustamos el término independiente correspondiente
        }
    }

    // Fase de sustitución hacia atrás para encontrar las soluciones
    vector<double> soluciones(n);  // Vector para almacenar las soluciones del sistema
    for (int i = n - 1; i >= 0; i--) {  // Empezamos desde la última ecuación hacia la primera
        soluciones[i] = resultados[i];  // Comenzamos con el término independiente ajustado
        for (int j = i + 1; j < n; j++) {
            soluciones[i] -= matriz[i][j] * soluciones[j];  // Restamos las contribuciones de las variables ya encontradas
        }
    }

    // Imprimir las soluciones del sistema
    cout << "Soluciones:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "X" << i + 1 << " = " << fixed << setprecision(4) << soluciones[i] << endl;
    }
}

int main() {
    int n;
    cout << "Ingrese el tamaño de la matriz (n x n): ";
    cin >> n;  // Leemos el tamaño de la matriz cuadrada

    vector<vector<double>> matriz(n, vector<double>(n));  // Declaramos la matriz de coeficientes (n x n)
    vector<double> resultados(n);  // Declaramos el vector de términos independientes (n)

    // Leemos la matriz extendida: coeficientes y términos independientes
    cout << "Ingrese los elementos de la matriz extendida (coeficientes de las ecuaciones y términos independientes):" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> matriz[i][j];  // Leemos los coeficientes de la matriz A
        }
        cin >> resultados[i];  // Leemos el término independiente correspondiente
    }

    // Llamamos a la función para realizar la eliminación gaussiana
    eliminacionGaussiana(matriz, resultados, n);

    return 0;
}