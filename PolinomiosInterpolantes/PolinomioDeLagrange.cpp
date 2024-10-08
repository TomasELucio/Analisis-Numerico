#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

// Función para calcular el polinomio básico de Lagrange L_i(x)
double Li(int i, const vector<double>& x, double valorX) {
    double resultado = 1.0;
    int n = x.size();

    for (int j = 0; j < n; ++j) {
        if (j != i) {
            resultado *= (valorX - x[j]) / (x[i] - x[j]);
        }
    }
    return resultado;
}

// Función para calcular los coeficientes de un polinomio expandido
vector<double> expandirLi(int i, const vector<double>& x) {
    int n = x.size();
    vector<double> coeficientes(n, 0);  // Coeficientes del polinomio expandido

    // Comenzamos con un polinomio constante igual a 1
    coeficientes[0] = 1.0;

    // Multiplicamos (x - x_j) para cada j != i
    for (int j = 0; j < n; ++j) {
        if (j != i) {
            vector<double> nuevo(n, 0);

            // Multiplicación de polinomios
            for (int k = n - 1; k >= 0; --k) {
                if (coeficientes[k] != 0) {
                    nuevo[k + 1] += coeficientes[k];
                    nuevo[k] -= coeficientes[k] * x[j];
                }
            }

            coeficientes = nuevo;
        }
    }

    // Dividimos los coeficientes por el denominador (x_i - x_j)
    double denominador = 1.0;
    for (int j = 0; j < n; ++j) {
        if (j != i) {
            denominador *= (x[i] - x[j]);
        }
    }

    for (double& coef : coeficientes) {
        coef /= denominador;
    }

    return coeficientes;
}

// Función para reducir el polinomio de Lagrange a su mínima expresión
vector<double> reducirPolinomioLagrange(const vector<double>& x, const vector<double>& y) {
    int n = x.size();
    vector<double> polinomio(n, 0);  // Inicializamos el polinomio

    // Sumamos y_i * L_i(x) para todos los i
    for (int i = 0; i < n; ++i) {
        vector<double> coeficientesLi = expandirLi(i, x);

        // Multiplicamos cada coeficiente de L_i(x) por y_i y lo sumamos al polinomio final
        for (int j = 0; j < n; ++j) {
            polinomio[j] += y[i] * coeficientesLi[j];
        }
    }

    return polinomio;
}

// Función para mostrar el polinomio expandido
void mostrarPolinomio(const vector<double>& polinomio) {
    int n = polinomio.size();

    cout << "f(x) = ";
    for (int i = n - 1; i >= 0; --i) {
        if (fabs(polinomio[i]) > 1e-6) {  // Ignorar coeficientes cercanos a 0
            if (i != n - 1 && polinomio[i] > 0) {
                cout << " + ";
            } else if (polinomio[i] < 0) {
                cout << " - ";
            }
            cout << fabs(polinomio[i]);
            if (i > 0) {
                cout << "x";
                if (i > 1) {
                    cout << "^" << i;
                }
            }
        }
    }
    cout << endl;
}

int main() {
    // Puntos de ejemplo (X, Y)
    vector<double> x = {0.5,1,1.5,2,2.5,3};  // Valores de X
    vector<double> y = {1,2.119,2.91,3.945,5.72,8.695};  // Valores de Y correspondientes

    // Reducir el polinomio de Lagrange a su mínima expresión
    vector<double> polinomio = reducirPolinomioLagrange(x, y);

    // Mostrar el polinomio reducido
    mostrarPolinomio(polinomio);

    return 0;
}
