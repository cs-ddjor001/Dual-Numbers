#include "Duals.h"
#include <cassert>

template<typename T>
bool nearlyEqual(T a, T b, T epsilon = 1e-5) 
{
    return std::abs(a - b) < epsilon;
}

void testArithmeticOperations() 
{
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

void testTrigonometricFunctions() 
{
    Duals<double> c(M_PI / 4, 1); // π/4 + ε

    // Test sin
    auto resultSin = sin(c);
    assert(std::abs(resultSin.getValue() - std::sqrt(2)/2) < 1e-12 && std::abs(resultSin.getDerivative() - std::sqrt(2)/2) < 1e-12);

    // Test cos
    auto resultCos = cos(c);
    assert(std::abs(resultCos.getValue() - std::sqrt(2)/2) < 1e-12 && std::abs(resultCos.getDerivative() + std::sqrt(2)/2) < 1e-12);

    auto resultTan = tan(c);
    assert(std::abs(resultTan.getValue() - 1) < 1e-12 && std::abs(resultTan.getDerivative() - 2) < 1e-12);

    std::cout << "Trigonometric functions tests passed." << std::endl;
}

void testInverseTrigonometricFunctions()
{
    // Test arcsin
    Duals<double> d_asin(0.5, 1); // arcsin(0.5) = π/6, derivative should be 1/sqrt(1 - 0.5^2) = 2/√3
    auto result_asin = arcsin(d_asin);
    assert(nearlyEqual(result_asin.getValue(), M_PI / 6));
    assert(nearlyEqual(result_asin.getDerivative(), 2 / std::sqrt(3)));

    // Test arccos
    Duals<double> d_acos(0.5, 1); // arccos(0.5) = π/3, derivative should be -1/sqrt(1 - 0.5^2) = -2/√3
    auto result_acos = arccos(d_acos);
    assert(nearlyEqual(result_acos.getValue(), M_PI / 3));
    assert(nearlyEqual(result_acos.getDerivative(), -2 / std::sqrt(3)));

    // Test arctan
    Duals<double> d_atan(1, 1); // arctan(1) = π/4, derivative should be 1/(1 + 1^2) = 1/2
    auto result_atan = arctan(d_atan);
    assert(nearlyEqual(result_atan.getValue(), M_PI / 4));
    assert(nearlyEqual(result_atan.getDerivative(), 0.5));

    std::cout << "All inverse trigonometric function tests passed.\n";
} 

void testPowFunction() 
{
    Duals<int> x(5, 1); // Initialize x as 5 with a derivative of 1

    Duals<int> f = pow(x, 2); // Compute f = x^2

    // Assert the value of f is 25 (since 5^2 = 25)
    assert(f.getValue() == 25);

    // Assert the derivative of f with respect to x is 10 (since 2*5 = 10)
    assert(f.getDerivative() == 10);

    std::cout << "Pow function tests passed." << std::endl;
}

void testAbs() 
{
    Duals<double> d1(3.0, 4.0);
    Duals<double> d2(-3.0, -4.0);
    
    auto result1 = abs(d1);
    auto result2 = abs(d2);
    
    assert(result1.getValue() == 3.0 && result1.getDerivative() == 4.0);
    assert(result2.getValue() == 3.0 && result2.getDerivative() == -4.0);
    
    std::cout << "testAbs passed.\n";
}

void testSqrt() 
{
    Duals<double> d(4.0, 2.0);
    Duals<double> d2(16.0, 8.0);
    auto result = sqrt(d);
    auto result2 = sqrt(d2);
    
    assert(nearlyEqual(result.getValue(), 2.0));
    assert(nearlyEqual(result.getDerivative(), 0.5)); // 0.5 * 2.0 / sqrt(4.0)

    assert(nearlyEqual(result2.getValue(), 4.0));
    assert(nearlyEqual(result2.getDerivative(), 1.0)); // 0.5 * 8.0 / sqrt(16.0)
    
    std::cout << "testSqrt passed.\n";
}

void testLog() 
{
    Duals<double> d(std::exp(1.0), 4.0);
    auto result = log(d);
    
    assert(nearlyEqual(result.getValue(), 1.0));
    assert(nearlyEqual(result.getDerivative(), 4.0 / std::exp(1.0)));
    
    std::cout << "testLog passed.\n";
}

void testExp() 
{
    Duals<double> d(1.0, 3.0);
    auto result = exp(d);
    
    assert(nearlyEqual(result.getValue(), std::exp(1.0)));
    assert(nearlyEqual(result.getDerivative(), 3.0 * std::exp(1.0)));
    
    std::cout << "testExp passed.\n";
}

void testComparisonOperators() 
{
    Duals<double> d1(1.0, 2.0);
    Duals<double> d2(1.0, 2.0);
    Duals<double> d3(2.0, 3.0);
    Duals<double> d4(2.0, 3.0);
    
    assert(d1 == d2);
    assert(d1 != d3);
    assert(d1 < d3);
    assert(d3 > d1);
    assert(d2 < d3);
    assert(d3 > d2);
    assert(d3 != d2);
    assert(d3 >= d4);
    assert(d4 <= d3);
    assert(d3 <= d4);
    assert(d4 >= d3);
    
    std::cout << "testComparisonOperators passed.\n";
}


int main() 
{
    testArithmeticOperations();
    testTrigonometricFunctions();
    testPowFunction();
    testAbs();
    testSqrt();
    testLog();
    testExp();
    testComparisonOperators();
    testInverseTrigonometricFunctions();
    std::cout << "All tests passed successfully." << std::endl;
    return 0;
}
