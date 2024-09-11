#include <iostream>
#include <vector>
#include <cmath>    // Para usar la función abs (valor absoluto)
#include <iomanip>  // Para manipular la salida de datos (formato, precisión)

using namespace std;

// Función para aplicar el método de Gauss-Seidel e imprimir cada iteración
bool gaussSeidel(vector<vector<double>>& matriz, vector<double>& resultados, vector<double>& aproximacion, int n, double tolerancia, int iteracionesMax) {
    vector<double> nuevaAproximacion(n);

    // Encabezado de la tabla
    cout << "Iteración\t";
    for (int i = 0; i < n; i++) {
        cout << "X" << i + 1 << "\t\t";
        cout << "|E" << i + 1 << "|\t\t";
    }
    cout << endl;
    
    for (int iteracion = 0; iteracion < iteracionesMax; iteracion++) {
        bool converge = true;

        // Mostrar el número de la iteración actual
        cout << iteracion + 1 << "\t\t";

        for (int i = 0; i < n; i++) {
            double suma = resultados[i];

            // Calcular la suma de los términos conocidos
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    suma -= matriz[i][j] * aproximacion[j];
                }
            }

            // Calcular el nuevo valor de la variable
            nuevaAproximacion[i] = suma / matriz[i][i];

            // Verificar la convergencia
            if (converge && fabs(nuevaAproximacion[i] - aproximacion[i]) > tolerancia) {
                converge = false;
            }

            // Imprimir el valor de la aproximación y el error
            double error = fabs(nuevaAproximacion[i] - aproximacion[i]);
            cout << fixed << setprecision(4) << nuevaAproximacion[i] << "\t\t" << error << "\t\t";

            // Actualizar el valor de la aproximación para la siguiente iteración
            aproximacion[i] = nuevaAproximacion[i];
        }
        cout << endl;

        // Si todas las variables han convergido, terminar
        if (converge) {
            return true;
        }
    }

    // Si se alcanzó el número máximo de iteraciones sin converger
    return false;
}

int main() {
    int n;
    double tolerancia;
    int iteracionesMax;

    cout << "Ingrese el tamaño de la matriz (n x n): ";
    cin >> n;

    vector<vector<double>> matriz(n, vector<double>(n));
    vector<double> resultados(n);
    vector<double> aproximacion(n, 0);  // Inicializamos la aproximación inicial en 0

    cout << "Ingrese los elementos de la matriz extendida (coeficientes de las ecuaciones y términos independientes):" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> matriz[i][j];
        }
        cin >> resultados[i];
    }

    cout << "Ingrese la tolerancia deseada: ";
    cin >> tolerancia;

    cout << "Ingrese el número máximo de iteraciones: ";
    cin >> iteracionesMax;

    if (gaussSeidel(matriz, resultados, aproximacion, n, tolerancia, iteracionesMax)) {
        cout << "El método ha convergido a las siguientes soluciones:" << endl;
        for (int i = 0; i < n; i++) {
            cout << "X" << i + 1 << " = " << aproximacion[i] << endl;
        }
    } else {
        cout << "El método no ha convergido después de " << iteracionesMax << " iteraciones." << endl;
    }

    return 0;
}