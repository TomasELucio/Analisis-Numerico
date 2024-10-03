#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
void regresionLineal(const vector<double>& x, const vector<double>& y, double& a0, double& a1);
void regresionLinealPotencial(const vector<double>& x, const vector<double>& y, double& a0, double& a1);
void regresionLinealExponencial(const vector<double>& x, const vector<double>& y, double& a0, double& a1);
double sumLin(const vector<double>& v);
double sumPot(const vector<double>& v);
double sumExp(const vector<double>& v);

int main() {
    vector<double> x = {1,2,3,4,5};
    vector<double> y = {0.5,1.7,3.4,5.7,8.4};

    double a0 = 0.0, a1 = 0.0;

    bool lineal = false;
    bool exponencial = true;
    bool potencial = false;
    bool decrecimiento = false;
    if(lineal){
        regresionLineal(x, y, a0, a1);
        cout << "La ecuación de la recta es: y = " << a0 << " + " << a1 << "x" << endl;
    }
    if (exponencial)
    {
        regresionLinealExponencial(x, y, a0, a1);
        cout << "La ecuación del modelo exponencial es: y = " << exp(a0) << "e^(" << a1<< "x)"<<endl;
    }
    if (potencial)
    {
        regresionLinealPotencial(x, y, a0, a1);
        cout << "La ecuación del modelo potencial es: y = "<< pow(10,a0) << "x^" << a1<<endl;
    }
    if(decrecimiento)
    {
        cout << "La ecuación de la recta es: y = "<< 1/a0 << "(x/()" << a1*(1/a0) << "+ x))"<<endl;
    }
    return 0;
}

double sumLin(const vector<double>& v) {
    double suma=0.0;
    int n = v.size();
    for (int i = 0; i < n; i++)
    {
        suma += v[i];
    }
    return suma;
}
double sumPot(const vector<double>& v) {
    double suma=0.0;
    int n = v.size();
    for (int i = 0; i < n; i++)
    {
        suma += log10(v[i]);
    }
    return suma;
}
double sumExp(const vector<double>& v) {
    double suma=0.0;
    int n = v.size();
    for (int i = 0; i < n; i++)
    {
        suma += log(v[i]);
    }
    return suma;
}


void regresionLineal(const vector<double>& x, const vector<double>& y, double& a0, double& a1) {
    int n = x.size();
    double sumX = sumLin(x);
    double sumY = sumLin(y);
    double sumXY = 0.0;
    double sumX2 = 0.0;

    for (int i = 0; i < n; ++i) {
        sumXY += log10(x[i]) * log10(y[i]);
        sumX2 += log10(x[i]) * log10(x[i]);
    }

    a1 = (n * sumXY - sumX * sumY) / (n * sumX2 - sumX * sumX);
    a0 = (sumY - a1 * sumX) / n;
}

void regresionLinealExponencial(const vector<double>& x, const vector<double>& y, double& a0, double& a1){
    int n = x.size();
    double sumX = sumLin(x);
    double sumY = sumExp(y);
    double sumXY = 0.0;
    double sumX2 = 0.0;

    for (int i = 0; i < n; ++i) {
        sumXY += x[i] * log(y[i]);
        sumX2 += x[i] * x[i];
    }

    a1 = (n * sumXY - sumX * sumY) / (n * sumX2 - sumX * sumX);
    a0 = (sumY - a1 * sumX) / n;
}

void regresionLinealPotencial(const vector<double>& x, const vector<double>& y, double& a0, double& a1) {
    int n = x.size();
    double sumX = sumPot(x);
    double sumY = sumPot(y);
    double sumXY = 0.0;
    double sumX2 = 0.0;

    for (int i = 0; i < n; ++i) {
        sumXY += log10(x[i]) * log10(y[i]);
        sumX2 += log10(x[i]) * log10(x[i]);
    }

    a1 = (n * sumXY - sumX * sumY) / (n * sumX2 - sumX * sumX);
    a0 = (sumY - a1 * sumX) / n;
}
