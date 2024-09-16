#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

double norma_columna(const vector<vector<double>>& A) {
    double max_sum = 0.0;
    int columnas = A[0].size();
    int filas = A.size();
    
    for (int j = 0; j < columnas; ++j) {
        double sum = 0.0;
        for (int i = 0; i < filas; ++i) {
            sum += fabs(A[i][j]);
        }
        if (sum > max_sum) {
            max_sum = sum;
        }
    }
    return max_sum;
}

bool gauss_jordan_inversa(vector<vector<double>>& A, vector<vector<double>>& A_inv) {
    int n = A.size();
    A_inv = vector<vector<double>>(n, vector<double>(n, 0.0));
    
    // Inicializar A_inv como la matriz identidad
    for (int i = 0; i < n; ++i) {
        A_inv[i][i] = 1.0;
    }
    
    for (int i = 0; i < n; ++i) {
        double pivot = A[i][i];
        if (fabs(pivot) < 1e-6) {
            return false; // La matriz no es invertible
        }
        
        // Dividir la fila por el pivote
        for (int j = 0; j < n; ++j) {
            A[i][j] /= pivot;
            A_inv[i][j] /= pivot;
        }
        
        // Hacer ceros en la columna del pivote
        for (int k = 0; k < n; ++k) {
            if (k != i) {
                double factor = A[k][i];
                for (int j = 0; j < n; ++j) {
                    A[k][j] -= factor * A[i][j];
                    A_inv[k][j] -= factor * A_inv[i][j];
                }
            }
        }
    }
    return true;
}

void imprimir_matriz(const vector<vector<double>>& matriz) {
    int filas = matriz.size();
    int columnas = matriz[0].size();
    
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            cout << setw(10) << fixed << setprecision(6) << matriz[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    // Definimos la matriz A
    vector<vector<double>> A = {
        {18.04, 6.10,4.10},
        {2.00,-9.00,7.10},
        {9.01,3.20,2.05}
    };
    
    cout << "Matriz A:" << endl;
    imprimir_matriz(A);
    
    double norma_A = norma_columna(A);
    
    vector<vector<double>> A_inv;
    if (!gauss_jordan_inversa(A, A_inv)) {
        cout << "La matriz no es invertible." << endl;
        return -1;
    }
    
    cout << "Matriz A inversa:" << endl;
    imprimir_matriz(A_inv);
    
    double norma_A_inv = norma_columna(A_inv);
    
    double numero_condicion = norma_A * norma_A_inv;
    
    cout << fixed << setprecision(4);
    cout << "Norma 1 de A (norma de columna): " << norma_A << endl;
    cout << "Norma 1 de A_inv (norma de columna): " << norma_A_inv << endl;
    cout << "Número de condición de la matriz A: " << numero_condicion << endl;

    return 0;
}
