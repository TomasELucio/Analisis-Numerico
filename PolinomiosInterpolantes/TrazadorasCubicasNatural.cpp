#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

struct CubicSpline {
    double a, b, c, d, x;
};

vector<CubicSpline> cubicSplineNatural(const vector<double>& x, const vector<double>& y);
double evaluateSpline(const vector<CubicSpline>& splines, double x);
void printReducedPolynomials(const vector<CubicSpline>& splines);

int main() {
    vector<double> x = {0, 1, 2, 3};
    vector<double> y = {1, 2.7182, 7.3891, 20.0855};

    vector<CubicSpline> splines = cubicSplineNatural(x, y);

    // Mostrar los polinomios reducidos
    printReducedPolynomials(splines);

    // Evaluar el spline en un punto
    double x_eval = 1.5;
    double y_eval = evaluateSpline(splines, x_eval);
    cout << "El valor interpolado en x = " << x_eval << " es y = " << y_eval << endl;

    return 0;
}

vector<CubicSpline> cubicSplineNatural(const vector<double>& x, const vector<double>& y) {
    int n = x.size() - 1;
    vector<double> h(n), alpha(n);
    for (int i = 0; i < n; ++i) {
        h[i] = x[i + 1] - x[i];
    }

    // Step 2: Calculate alpha values
    for (int i = 1; i < n; ++i) {
        alpha[i] = (3 / h[i]) * (y[i + 1] - y[i]) - (3 / h[i - 1]) * (y[i] - y[i - 1]);
    }

    // Step 3: Solve the tridiagonal system
    vector<double> l(n + 1), mu(n), z(n + 1);
    l[0] = 1.0;
    mu[0] = z[0] = 0.0;

    for (int i = 1; i < n; ++i) {
        l[i] = 2 * (x[i + 1] - x[i - 1]) - h[i - 1] * mu[i - 1];
        mu[i] = h[i] / l[i];
        z[i] = (alpha[i] - h[i - 1] * z[i - 1]) / l[i];
    }

    l[n] = 1.0;
    z[n] = 0.0;

    vector<double> c(n + 1), b(n), d(n);
    for (int j = n - 1; j >= 0; --j) {
        c[j] = z[j] - mu[j] * c[j + 1];
        b[j] = (y[j + 1] - y[j]) / h[j] - h[j] * (c[j + 1] + 2 * c[j]) / 3;
        d[j] = (c[j + 1] - c[j]) / (3 * h[j]);
    }

    // Step 7: Build the spline coefficients
    vector<CubicSpline> splines(n);
    for (int i = 0; i < n; ++i) {
        splines[i] = {y[i], b[i], c[i], d[i], x[i]};
    }

    return splines;
}

double evaluateSpline(const vector<CubicSpline>& splines, double x) {
    int n = splines.size();
    CubicSpline s;
    for (int i = 0; i < n; ++i) {
        if (x >= splines[i].x && (i == n - 1 || x < splines[i + 1].x)) {
            s = splines[i];
            break;
        }
    }

    double dx = x - s.x;
    return s.a + s.b * dx + s.c * dx * dx + s.d * dx * dx * dx;
}

void printReducedPolynomials(const vector<CubicSpline>& splines) {
    cout << fixed << setprecision(4);
    for (int i = 0; i < splines.size(); ++i) {
        double a = splines[i].a;
        double b = splines[i].b;
        double c = splines[i].c;
        double d = splines[i].d;
        double x0 = splines[i].x;

        // Expand the polynomial S_i(x) = a + b * (x - x0) + c * (x - x0)^2 + d * (x - x0)^3
        double a_reduced = a - b * x0 + c * x0 * x0 - d * x0 * x0 * x0;
        double b_reduced = b - 2 * c * x0 + 3 * d * x0 * x0;
        double c_reduced = c - 3 * d * x0;
        double d_reduced = d;

        cout << "Polinomio " << i << " en el intervalo [" << x0 << ", " << splines[i + 1].x << "]:" << endl;
        cout << "S_" << i << "(x) = " << a_reduced
             << " + " << b_reduced << " * x"
             << " + " << c_reduced << " * x^2"
             << " + " << d_reduced << " * x^3" << endl;
        cout << endl;
    }
}