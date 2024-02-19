#include "Duals.h"
#include <cassert>

void testArithmeticOperations() {
    Duals<double> a(5, 1); // 5 + ε
    Duals<double> b(3, 2); // 3 + 2ε

    // Test addition
    auto resultAdd = a + b;
    assert(resultAdd.getValue() == 8 && resultAdd.getDerivative() == 3);

    // Test subtraction
    auto resultSub = a - b;
    assert(resultSub.getValue() == 2 && resultSub.getDerivative() == -1);

    // Test multiplication
    auto resultMul = a * b;
    assert(resultMul.getValue() == 15 && resultMul.getDerivative() == 11);

    // Test division
    auto resultDiv = a / b;
    assert(resultDiv.getValue() == 5.0/3.0 && resultDiv.getDerivative() == -1.0/9.0);
}

void testTrigonometricFunctions() {
    Duals<double> c(M_PI / 4, 1); // π/4 + ε

    // Test sin
    auto resultSin = sin(c);
    assert(std::abs(resultSin.getValue() - std::sqrt(2)/2) < 1e-12 && std::abs(resultSin.getDerivative() - std::sqrt(2)/2) < 1e-12);

    // Test cos
    auto resultCos = cos(c);
    assert(std::abs(resultCos.getValue() - std::sqrt(2)/2) < 1e-12 && std::abs(resultCos.getDerivative() + std::sqrt(2)/2) < 1e-12);
}

int main() {
    testArithmeticOperations();
    testTrigonometricFunctions();
    std::cout << "All tests passed successfully." << std::endl;
    return 0;
}
