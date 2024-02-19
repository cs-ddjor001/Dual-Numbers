#include "Duals.h"
#include <cassert>

void testArithmeticOperations() {
    Duals<double> a(5.0, 1.0); // 5 + ε
    Duals<double> b(3.0, 1.0); // 3 + ε

    // Test addition
    auto resultAdd = a + b;
    assert(resultAdd.getValue() == 8 && resultAdd.getDerivative() == 2);

    // Test subtraction
    auto resultSub = a - b;
    assert(resultSub.getValue() == 2 && resultSub.getDerivative() == 0);

    // Test multiplication
    auto resultMul = a * b;
    assert(resultMul.getValue() == 15 && resultMul.getDerivative() == 8);

    // Test division
    auto resultDiv = a / b;
    assert(resultDiv.getValue() == 5.0/3.0 && resultDiv.getDerivative() == -2.0/9.0);

    std::cout << "Arithmetic Operations tests passed." << std::endl;
}

void testTrigonometricFunctions() {
    Duals<double> c(M_PI / 4, 1); // π/4 + ε

    // Test sin
    auto resultSin = sin(c);
    assert(std::abs(resultSin.getValue() - std::sqrt(2)/2) < 1e-12 && std::abs(resultSin.getDerivative() - std::sqrt(2)/2) < 1e-12);

    // Test cos
    auto resultCos = cos(c);
    assert(std::abs(resultCos.getValue() - std::sqrt(2)/2) < 1e-12 && std::abs(resultCos.getDerivative() + std::sqrt(2)/2) < 1e-12);

    std::cout << "Trigonometric functions tests passed." << std::endl;
}

void testPowFunction() {
    Duals<int> x(5, 1); // Initialize x as 5 with a derivative of 1

    Duals<int> f = pow(x, 2); // Compute f = x^2

    // Assert the value of f is 25 (since 5^2 = 25)
    assert(f.getValue() == 25);

    // Assert the derivative of f with respect to x is 10 (since 2*5 = 10)
    assert(f.getDerivative() == 10);

    std::cout << "Pow function tests passed." << std::endl;
}


int main() {
    testArithmeticOperations();
    testTrigonometricFunctions();
    testPowFunction();
    std::cout << "All tests passed successfully." << std::endl;
    return 0;
}
