#include <iostream>   
#include <vector>     
#include <iomanip>    

using namespace std;


void eliminacionGaussiana(vector<vector<double>>& matriz, vector<double>& resultados, int n) {
    // Fase de eliminación para convertir la matriz en triangular superior
    for (int i = 0; i < n; i++) {
        double diag = matriz[i][i];  
        for (int j = 0; j < n; j++) {
            matriz[i][j] /= diag;  
        }
        resultados[i] /= diag;  // Ajustamos el término independiente

        // Hacemos ceros debajo de la diagonal principal
        for (int k = i + 1; k < n; k++) {
            double factor = matriz[k][i];  // Factor por el cual multiplicaremos la fila para restarla
            for (int j = 0; j < n; j++) {
                matriz[k][j] -= factor * matriz[i][j];  // Restamos la fila i multiplicada por el factor
            }
            resultados[k] -= factor * resultados[i]; 
        }
    }

    // Fase de sustitución hacia atrás para encontrar las soluciones
    vector<double> soluciones(n);  
    for (int i = n - 1; i >= 0; i--) {  
        soluciones[i] = resultados[i];  
        for (int j = i + 1; j < n; j++) {
            soluciones[i] -= matriz[i][j] * soluciones[j];
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
    double error = 0.0001;
    cout << "Ingrese el tamaño de la matriz (n x n): ";
    cin >> n;  

    vector<vector<double>> matriz(n, vector<double>(n));  
    vector<double> resultados(n); 

    cout << "Ingrese los elementos de la matriz extendida (coeficientes de las ecuaciones y términos independientes):" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> matriz[i][j];  
        }
        cin >> resultados[i];  
    }

    eliminacionGaussiana(matriz, resultados, n);

    return 0;
}