/*
#include <iostream>
#include <vector>

using namespace std;

// Función para descomponer la matriz A en L y U
void descomposicionLU(vector<vector<double>>& A, vector<vector<double>>& L, vector<vector<double>>& U, int n) {
    for (int i = 0; i < n; i++) {
        // Calcular la matriz U
        for (int j = i; j < n; j++) {
            double suma = 0;
            for (int k = 0; k < i; k++) {
                suma += L[i][k] * U[k][j];
            }
            U[i][j] = A[i][j] - suma;
        }

        // Calcular la matriz L
        for (int j = i; j < n; j++) {
            if (i == j) {
                L[i][i] = 1;  // Diagonal de L es 1
            } else {
                double suma = 0;
                for (int k = 0; k < i; k++) {
                    suma += L[j][k] * U[k][i];
                }
                L[j][i] = (A[j][i] - suma) / U[i][i];
            }
        }
    }
}

// Función para resolver LY = B mediante sustitución hacia adelante
vector<double> sustitucionHaciaAdelante(vector<vector<double>>& L, vector<double>& B, int n) {
    vector<double> Y(n);
    for (int i = 0; i < n; i++) {
        double suma = 0;
        for (int j = 0; j < i; j++) {
            suma += L[i][j] * Y[j];
        }
        Y[i] = (B[i] - suma);
    }
    return Y;
}

// Función para resolver UX = Y mediante sustitución hacia atrás
vector<double> sustitucionHaciaAtras(vector<vector<double>>& U, vector<double>& Y, int n) {
    vector<double> X(n);
    for (int i = n - 1; i >= 0; i--) {
        double suma = 0;
        for (int j = i + 1; j < n; j++) {
            suma += U[i][j] * X[j];
        }
        X[i] = (Y[i] - suma) / U[i][i];
    }
    return X;
}

int main() {
    int n;
    cout << "Ingrese el tamaño de la matriz (n x n): ";
    cin >> n;

    vector<vector<double>> A(n, vector<double>(n));
    vector<vector<double>> L(n, vector<double>(n, 0));
    vector<vector<double>> U(n, vector<double>(n, 0));
    vector<double> B(n);

    cout << "Ingrese los elementos de la matriz A:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> A[i][j];
        }
    }

    cout << "Ingrese los términos independientes del vector B:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> B[i];
    }

    // Descomposición de A en L y U
    descomposicionLU(A, L, U, n);

    // Resolución de LY = B
    vector<double> Y = sustitucionHaciaAdelante(L, B, n);

    // Resolución de UX = Y
    vector<double> X = sustitucionHaciaAtras(U, Y, n);

    // Imprimir la solución
    cout << "Las soluciones del sistema son:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "X" << i + 1 << " = " << X[i] << endl;
    }

    return 0;
}*/


#include <iostream>
#include <vector>
#include <iomanip>  // Para manipular la salida de datos (formato, precisión)

using namespace std;

// Función para descomponer la matriz A en L y U
bool descomposicionLU(vector<vector<double>>& A, vector<vector<double>>& L, vector<vector<double>>& U, int n) {
    for (int i = 0; i < n; i++) {
        // Calcular la matriz U
        for (int j = i; j < n; j++) {
            double suma = 0;
            for (int k = 0; k < i; k++) {
                suma += L[i][k] * U[k][j];
            }
            U[i][j] = A[i][j] - suma;
        }

        // Calcular la matriz L
        for (int j = i + 1; j < n; j++) {
            if (U[i][i] == 0) {
                cout << "La descomposición LU no es posible, ya que se encontró un cero en la diagonal de U." << endl;
                return false;
            }
            double suma = 0;
            for (int k = 0; k < i; k++) {
                suma += L[j][k] * U[k][i];
            }
            L[j][i] = (A[j][i] - suma) / U[i][i];
        }
    }
    return true;
}

// Función para resolver LY = B mediante sustitución hacia adelante
vector<double> sustitucionHaciaAdelante(vector<vector<double>>& L, vector<double>& B, int n) {
    vector<double> Y(n);
    for (int i = 0; i < n; i++) {
        double suma = 0;
        for (int j = 0; j < i; j++) {
            suma += L[i][j] * Y[j];
        }
        Y[i] = (B[i] - suma);
    }
    return Y;
}

// Función para resolver UX = Y mediante sustitución hacia atrás
vector<double> sustitucionHaciaAtras(vector<vector<double>>& U, vector<double>& Y, int n) {
    vector<double> X(n);
    for (int i = n - 1; i >= 0; i--) {
        double suma = 0;
        for (int j = i + 1; j < n; j++) {
            suma += U[i][j] * X[j];
        }
        X[i] = (Y[i] - suma) / U[i][i];
    }
    return X;
}

int main() {
    int n = 3;

    vector<vector<double>> A = {
        {9, 3, 2},
        {2, -9, 7},
        {7, -2, 9}
    };
    vector<vector<double>> L(n, vector<double>(n, 0));
    vector<vector<double>> U(n, vector<double>(n, 0));
    vector<double> B = {4, 6, 3};

    // Descomposición de A en L y U
    if (descomposicionLU(A, L, U, n)) {
        // Resolución de LY = B
        vector<double> Y = sustitucionHaciaAdelante(L, B, n);

        // Resolución de UX = Y
        vector<double> X = sustitucionHaciaAtras(U, Y, n);

        // Imprimir la solución
        cout << "Las soluciones del sistema son:" << endl;
        for (int i = 0; i < n; i++) {
            cout << "X" << i + 1 << " = " << fixed << setprecision(4) << X[i] << endl;
        }
    } else {
        cout << "No se pudo realizar la descomposición LU." << endl;
    }

    return 0;
}