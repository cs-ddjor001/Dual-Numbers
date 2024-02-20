#include "Duals.h"

using namespace std;

int main() {
    // Test basic construction
    Duals<double> a(5.0, 1.0); // Represents the number 5 with a derivative of 1
    Duals<double> b(3.0, 1.0); // Represents the number 3 with a derivative of 1

    // Test arithmetic operations
    auto sum = a + b;
    auto difference = a - b;
    auto product = a * b;
    auto quotient = a / b;

    cout << "Sum: " << sum << endl;
    cout << "Difference: " << difference << endl;
    cout << "Product: " << product << endl;
    cout << "Quotient: " << quotient << endl;

    // Test sin and cos functions
    Duals<double> c(M_PI / 4, 1); // pi/4, derivative 1
    auto sinResult = sin(c);
    auto cosResult = cos(c);

    cout << "Sin(pi/4): " << sinResult << endl;
    cout << "Cos(pi/4): " << cosResult << endl;

    // Advanced test: Function composition
    // f(x) = sin(x^2), f'(x) = 2x*cos(x^2), let x = pi/4
    Duals<double> d(M_PI / 4, 1); // pi/4, derivative 1
    auto composedFunction = sin(d * d);
    cout << "Sin((pi/4)^2): " << composedFunction << endl;

    // Test function f as a function of x
    Duals<int> x (5, 1);

    Duals<int> f = pow(x, 2);

    cout << "Value of F(x) = x^2 when x = 5, is  " << f.getValue() << endl;
    cout << "Derivative of F wrt x = " << f.getDerivative() << endl;

    return 0;
}
