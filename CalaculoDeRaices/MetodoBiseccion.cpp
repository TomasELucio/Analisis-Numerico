#include <iostream>
#include <cmath>
#include <functional>

using namespace std;


double evaluarFuncion(const function<double(double)>& funcion, double x) {
    return funcion(x);
}


double biseccion(const function<double(double)>& funcion, double a, double b, double tolerancia) {
    double c;  // Punto medio del intervalo


    while ((b - a) / 2.0 > tolerancia) {
        c = (a + b) / 2.0;

        if (evaluarFuncion(funcion, c) == 0.0) {
            break;
        }
        
        else if (evaluarFuncion(funcion, a) * evaluarFuncion(funcion, c) < 0) {
            b = c;
        }
        
        else {
            a = c;
        }
    }

    return c;  
}

int main() {
    double longitudIntervalo, tolerancia;
    double dominioInicio = -100, dominioFin = 0;  // Definimos el dominio de búsqueda
   
    auto funcion = [](double x) {
        return (2 - ((x+2)/exp(x)));
    };
    
    cout << "Ingrese la longitud del intervalo de búsqueda: ";
    cin >> longitudIntervalo;

    cout << "Ingrese la tolerancia de error: ";
    cin >> tolerancia;

    double a = dominioInicio;  
    bool raizEncontrada = false;


    while (a + longitudIntervalo <= dominioFin) {
        double b = a + longitudIntervalo;

        
        if (evaluarFuncion(funcion, a) * evaluarFuncion(funcion, b) <= 0) {
            
            double raiz = biseccion(funcion, a, b, tolerancia);
            cout << "Raíz encontrada en el intervalo [" << a << ", " << b << "]: " << raiz << endl;
            raizEncontrada = true;
        }

        a = b;  
    }

    
    if (!raizEncontrada) {
        cout << "No se encontraron raíces en el dominio dado." << endl;
    }

    return 0;
}