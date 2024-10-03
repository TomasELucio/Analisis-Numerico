#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Función para calcular las diferencias divididas
vector<vector<double>> diferenciasDivididas(const vector<double>& x, const vector<double>& y) {
    int n = x.size();
    vector<vector<double>> tabla(n, vector<double>(n));  // Tabla de diferencias divididas

    // Llenar la primera columna con los valores de y
    for (int i = 0; i < n; ++i) {
        tabla[i][0] = y[i];
    }

    // Calcular las diferencias divididas
    for (int j = 1; j < n; ++j) {
        for (int i = 0; i < n - j; ++i) {
            tabla[i][j] = (tabla[i + 1][j - 1] - tabla[i][j - 1]) / (x[i + j] - x[i]);
        }
    }

    return tabla;
}

// Función para construir el polinomio de interpolación de Newton (f_n(x))
string construirPolinomioNewton(const vector<double>& x, const vector<vector<double>>& tabla) {
    string polinomio = to_string(tabla[0][0]);  // Primer coeficiente a0

    // Construir el polinomio f_n(x)
    for (int i = 1; i < x.size(); ++i) {
        polinomio += " + (" + to_string(tabla[0][i]) + ")";  // Coeficiente a_i
        for (int j = 0; j < i; ++j) {
            polinomio += "(x - " + to_string(x[j]) + ")";  // Términos (x - x_j)
        }
    }

    return polinomio;
}

int main() {
    // Puntos de ejemplo (X, Y)
    vector<double> x = {0, 1, 2, 3};  // Valores de X
    vector<double> y = {1, 2.7182, 7.3891, 20.0855};  // Valores de Y correspondientes

    // Calcular la tabla de diferencias divididas
    vector<vector<double>> tabla = diferenciasDivididas(x, y);

    // Mostrar la tabla de diferencias divididas
    cout << "Tabla de diferencias divididas:" << endl;
    for (int i = 0; i < x.size(); ++i) {
        for (int j = 0; j < x.size() - i; ++j) {
            cout << tabla[i][j] << "\t";
        }
        cout << endl;
    }

    // Construir y mostrar el polinomio f_n(x)
    string polinomio = construirPolinomioNewton(x, tabla);
    cout << "El polinomio f_n(x) es: f_n(x) = " << polinomio << endl;

    return 0;
}