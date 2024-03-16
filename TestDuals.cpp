#include "Duals.h"
#include <cassert>
#include <sstream>

using namespace std;

void testConstructorsSingleVariable() 
{
    // Test default constructor
    Duals<1, int> a;
    assert(a.getValue() == 0);
    assert(a.getDerivative() == 0);

    // Test constructor with value only
    Duals<1, int> b(2);
    assert(b.getValue() == 2);
    assert(b.getDerivative() == 0);

    // Test constructor with value and derivative
    Duals<1, int> c(3, 4);
    assert(c.getValue() == 3);
    assert(c.getDerivative() == 4);

    cout << "All single-variable constructors passed!" << endl;
}

void testConstructorsMultivariable() 
{
    // Test default constructor
    Duals<3, int> a;
    assert(a.getValue() == 0);
    assert(a.getDerivative(0) == 0);
    assert(a.getDerivative(1) == 0);
    assert(a.getDerivative(2) == 0);

    // Test constructor with value only
    Duals<3, int> b(2);
    assert(b.getValue() == 2);
    assert(b.getDerivative(0) == 0);
    assert(b.getDerivative(1) == 0);
    assert(b.getDerivative(2) == 0);

    // Test constructor with value and derivative
    Duals<3, int> c(3, {4, 5, 6});
    assert(c.getValue() == 3);
    assert(c.getDerivative(0) == 4);
    assert(c.getDerivative(1) == 5);
    assert(c.getDerivative(2) == 6);

    cout << "All multi-variable constructors passed!" << endl;
}

void testGettersAndSettersSingleVariable() 
{
    // Test getters and setters for single variable dual numbers
    Duals<1, float> d;
    d.setValue(2.0);
    assert(d.getValue() == 2.0);

    d.setDerivative(3.0);
    assert(d.getDerivative() == 3.0);

    cout << "Getters and Setters for single-variable passed!" << endl;
}

void testGettersAndSettersMultivariable() 
{
    // Test getters and setters for multivariable dual numbers
    Duals<3, float> d;
    d.setValue(2.0);
    assert(d.getValue() == 2.0);

    d.setDerivative(0, 3.0);
    d.setDerivative(1, 4.0);
    d.setDerivative(2, 5.0);
    assert(d.getDerivative(0) == 3.0);
    assert(d.getDerivative(1) == 4.0);
    assert(d.getDerivative(2) == 5.0);

    cout << "Getters and Setters for multi-variable passed!" << endl;
}

void testSingleVariableArithmeticOperators() 
{
    // Test addition operator
    {
        Duals<1, double> x(2.0, 3.0); // Value = 2.0, Derivative = 3.0
        Duals<1, double> y(3.0, 4.0); // Value = 3.0, Derivative = 4.0
        Duals<1, double> result = x + y;

        // Check value
        assert(fabs(result.getValue() - (2.0 + 3.0)) < EPSILON);

        // Check derivative
        assert(fabs(result.getDerivative() - (3.0 + 4.0)) < EPSILON);
    }

    // Test subtraction operator
    {
        Duals<1, double> x(5.0, 7.0); // Value = 5.0, Derivative = 7.0
        Duals<1, double> y(3.0, 4.0); // Value = 3.0, Derivative = 4.0
        Duals<1, double> result = x - y;

        // Check value
        assert(fabs(result.getValue() - (5.0 - 3.0)) < EPSILON);

        // Check derivative
        assert(fabs(result.getDerivative() - (7.0 - 4.0)) < EPSILON);
    }

    // Test multiplication operator
    {
        Duals<1, double> x(2.0, 3.0); // Value = 2.0, Derivative = 3.0
        Duals<1, double> y(3.0, 4.0); // Value = 3.0, Derivative = 4.0
        Duals<1, double> result = x * y;

        // Check value
        assert(fabs(result.getValue() - (2.0 * 3.0)) < EPSILON);

        // Check derivative
        assert(fabs(result.getDerivative() - (2.0 * 4.0 + 3.0 * 3.0)) < EPSILON);
    }

    // Test division operator
    {
        Duals<1, double> x(6.0, 7.0); // Value = 6.0, Derivative = 7.0
        Duals<1, double> y(3.0, 4.0); // Value = 3.0, Derivative = 4.0
        Duals<1, double> result = x / y;

        // Check value
        assert(fabs(result.getValue() - (6.0 / 3.0)) < EPSILON);

        // Check derivative
        double expected_derivative = (7.0 * 3.0 - 6.0 * 4.0) / (3.0 * 3.0);
        assert(fabs(result.getDerivative() - expected_derivative) < EPSILON);
    }

    cout << "All single-variable arithmetic operator tests passed!" << endl;
}

void testMultiVariableArithmeticOperators() 
{
    // Test addition operator
    {
        Duals<3, double> x(2.0, {3.0, 1.0, 5.0}); // Value = 2.0, Derivatives = {3.0, 1.0, 5.0}
        Duals<3, double> y(3.0, {4.0, 2.0, 1.0}); // Value = 3.0, Derivatives = {4.0, 2.0, 1.0}
        Duals<3, double> result = x + y;

        // Check value
        assert(fabs(result.getValue() - (2.0 + 3.0)) < EPSILON);

        // Check derivatives
        for (size_t i = 0; i < 3; ++i) 
        {
            assert(fabs(result.getDerivative(i) - (x.getDerivative(i) + y.getDerivative(i))) < EPSILON);
        }
    }

    // Test subtraction operator
    {
        Duals<3, double> x(5.0, {7.0, 2.0, 6.0}); // Value = 5.0, Derivatives = {7.0, 2.0, 6.0}
        Duals<3, double> y(3.0, {4.0, 1.0, 3.0}); // Value = 3.0, Derivatives = {4.0, 1.0, 3.0}
        Duals<3, double> result = x - y;

        // Check value
        assert(fabs(result.getValue() - (5.0 - 3.0)) < EPSILON);

        // Check derivatives
        for (size_t i = 0; i < 3; ++i) {
            assert(fabs(result.getDerivative(i) - (x.getDerivative(i) - y.getDerivative(i))) < EPSILON);
        }
    }

    // Test multiplication operator
    {
        Duals<3, double> x(2.0, {3.0, 1.0, 5.0}); // Value = 2.0, Derivatives = {3.0, 1.0, 5.0}
        Duals<3, double> y(3.0, {4.0, 2.0, 1.0}); // Value = 3.0, Derivatives = {4.0, 2.0, 1.0}
        Duals<3, double> result = x * y;

        // Check value
        assert(fabs(result.getValue() - (2.0 * 3.0)) < EPSILON);

        // Check derivatives
        assert(fabs(result.getDerivative(0) - (2.0 * 4.0 + 3.0 * 3.0)) < EPSILON);
        assert(fabs(result.getDerivative(1) - (2.0 * 2.0 + 3.0 * 1.0)) < EPSILON);
        assert(fabs(result.getDerivative(2) - (2.0 * 1.0 + 3.0 * 5.0)) < EPSILON);
    }

    // Test division operator
    {
        Duals<3, double> x(6.0, {7.0, 2.0, 6.0}); // Value = 6.0, Derivatives = {7.0, 2.0, 6.0}
        Duals<3, double> y(3.0, {4.0, 1.0, 3.0}); // Value = 3.0, Derivatives = {4.0, 1.0, 3.0}
        Duals<3, double> result = x / y;

        // Check value
        assert(fabs(result.getValue() - (6.0 / 3.0)) < EPSILON);

        // Check derivatives
        double expected_derivative0 = (7.0 * 3.0 - 6.0 * 4.0) / (3.0 * 3.0);
        double expected_derivative1 = (2.0 * 3.0 - 6.0 * 1.0) / (3.0 * 3.0);
        double expected_derivative2 = (6.0 * 3.0 - 6.0 * 3.0) / (3.0 * 3.0);
        assert(fabs(result.getDerivative(0) - expected_derivative0) < EPSILON);
        assert(fabs(result.getDerivative(1) - expected_derivative1) < EPSILON);
        assert(fabs(result.getDerivative(2) - expected_derivative2) < EPSILON);
    }

    cout << "All multi-variable arithmetic operator tests passed!" << endl;
}

void testSingleVariableComparisonOperators() 
{
    // Test less than operator
    {
        Duals<1, double> x(2.0, 3.0); // Value = 2.0, Derivative = 3.0
        Duals<1, double> y(3.0, 4.0); // Value = 3.0, Derivative = 4.0

        // x < y
        assert(x < y);

        // y < x should be false
        assert(!(y < x));

        // x < x should be false
        assert(!(x < x));
    }

    // Test greater than operator
    {
        Duals<1, double> x(5.0, 7.0); // Value = 5.0, Derivative = 7.0
        Duals<1, double> y(3.0, 4.0); // Value = 3.0, Derivative = 4.0

        // x > y
        assert(x > y);

        // y > x should be false
        assert(!(y > x));

        // x > x should be false
        assert(!(x > x));
    }

    // Test equality operator
    {
        Duals<1, double> x(2.0, 3.0); // Value = 2.0, Derivative = 3.0
        Duals<1, double> y(2.0, 3.0); // Value = 2.0, Derivative = 4.0

        // x == y should be true
        assert(x == y);

        // x == x should be true
        assert(x == x);
    }

    // Test inequality operator
    {
        Duals<1, double> x(5.0, 7.0); // Value = 5.0, Derivative = 7.0
        Duals<1, double> y(3.0, 4.0); // Value = 3.0, Derivative = 4.0

        // x != y should be true
        assert(x != y);

        // x != x should be false
        assert(!(x != x));
    }

    // Test less than or equal to operator
    {
        Duals<1, double> x(2.0, 3.0); // Value = 2.0, Derivative = 3.0
        Duals<1, double> y(3.0, 4.0); // Value = 3.0, Derivative = 4.0

        // x <= y
        assert(x <= y);

        // y <= x should be false
        assert(!(y <= x));

        // x <= x should be true
        assert(x <= x);
    }

    // Test greater than or equal to operator
    {
        Duals<1, double> x(5.0, 7.0); // Value = 5.0, Derivative = 7.0
        Duals<1, double> y(3.0, 4.0); // Value = 3.0, Derivative = 4.0

        // x >= y
        assert(x >= y);

        // y >= x should be false
        assert(!(y >= x));

        // x >= x should be true
        assert(x >= x);
    }

    cout << "All single-variable comparison operator tests passed!" << endl;
}

void testComparisonOperatorsMultivariable() 
{
    // Define dual numbers
    Duals<3, int> a(2, {3, 4, 5});
    Duals<3, int> b(2, {4, 4, 5});
    Duals<3, int> c(2, {3, 4, 6});
    Duals<3, int> d(3, {3, 4, 5});

    // Test ==
    assert(a == a);
    assert(!(a == b));
    assert(!(a == c));
    assert(!(a == d));

    // Test !=
    assert(!(a != a));
    assert(a != b);
    assert(a != c);
    assert(a != d);

    // Test <
    assert(!(a < a));
    assert(a < b);
    assert(a < c);
    assert(a < d);
    assert(!(c < a));
    assert(!(d < a));

    // Test <=
    assert(a <= a);
    assert(a <= b);
    assert(a <= c);
    assert(a <= d);
    assert(!(c <= a));
    assert(!(d <= a));

    // Test >
    assert(!(a > a));
    assert(!(a > b));
    assert(!(a > c));
    assert(!(a > d));
    assert(c > a);
    assert(d > a);

    // Test >=
    assert(a >= a);
    assert(!(a >= b));
    assert(!(a >= c));
    assert(!(a >= d));
    assert(c >= a);
    assert(d >= a);

    cout << "All multi-variable comparison operator tests passed!" << endl;
}

void testTrigFunctionsSingleVariable()
{
    {
        /* Testing The Sin Function */
        Duals<1, double> x(0.5, 1.0); // Value = 0.5, Derivative = 1.0
        Duals<1, double> result = sin(x);

        // Check value
        assert(fabs(result.getValue() - sin(0.5)) < EPSILON);

        // Check derivative
        assert(fabs(result.getDerivative() - cos(0.5)) < EPSILON);
    }
    
    {
        /* Testing The Cos Function */
        Duals<1, double> x(0.5, 1.0); // Value = 0.5, Derivative = 1.0
        Duals<1, double> result = cos(x);

        // Check value
        assert(fabs(result.getValue() - cos(0.5)) < EPSILON);

        // Check derivative
        assert(fabs(result.getDerivative() + sin(0.5)) < EPSILON);
    }

    {
        /* Testing The Tan Function */
        Duals<1, double> x(0.5, 1.0); // Value = 0.5, Derivative = 1.0
        Duals<1, double> result = tan(x);

        // Check value
        assert(fabs(result.getValue() - tan(0.5)) < EPSILON);

        // Check derivative
        double sec_sq = 1 / (cos(0.5) * cos(0.5));
        assert(fabs(result.getDerivative() - sec_sq) < EPSILON);
    }

    {
        /* Testing The ArcSin Function */
        Duals<1, double> x(0.5, 1.0); // Value = 0.5, Derivative = 1.0
        Duals<1, double> result = arcsin(x);

        // Check value
        assert(fabs(result.getValue() - asin(0.5)) < EPSILON);

        // Check derivative
        double sqrt_val = sqrt(1.0 - 0.5 * 0.5);
        assert(fabs(result.getDerivative() - 1.0 / sqrt_val) < EPSILON);
    }

    {
        /* Testing The ArcCos Function */
        Duals<1, double> x(0.5, 1.0); // Value = 0.5, Derivative = 1.0
        Duals<1, double> result = arccos(x);

        // Check value
        assert(fabs(result.getValue() - acos(0.5)) < EPSILON);

        // Check derivative
        double sqrt_val = sqrt(1.0 - 0.5 * 0.5);
        assert(fabs(result.getDerivative() + 1.0 / sqrt_val) < EPSILON);
    }

    {
        /* Testing The ArcTan Function */
        Duals<1, double> x(0.5, 1.0); // Value = 0.5, Derivative = 1.0
        Duals<1, double> result = arctan(x);

        // Check value
        assert(fabs(result.getValue() - atan(0.5)) < EPSILON);

        // Check derivative
        double denom = 1.0 + 0.5 * 0.5;
        assert(fabs(result.getDerivative() - 1.0 / denom) < EPSILON);
    }
    
    cout << "All single-variable trigonometric function tests passed!" << endl;
}

void testMultivariableTrigFunctions()
{
    // Test sine function
    {
        Duals<3, double> x(0.5, {1.0, 0.0, 0.0}); // Value = 0.5, Derivatives = {1.0, 0.0, 0.0}
        Duals<3, double> result = sin(x);

        // Check value
        assert(fabs(result.getValue() - sin(0.5)) < EPSILON);

        // Check derivatives
        assert(fabs(result.getDerivative(0) - cos(0.5)) < EPSILON);
        assert(fabs(result.getDerivative(1)) < EPSILON);
        assert(fabs(result.getDerivative(2)) < EPSILON);
    }

    // Test cosine function
    {
        Duals<3, double> x(0.5, {1.0, 0.0, 0.0}); // Value = 0.5, Derivatives = {1.0, 0.0, 0.0}
        Duals<3, double> result = cos(x);

        // Check value
        assert(fabs(result.getValue() - cos(0.5)) < EPSILON);

        // Check derivatives
        assert(fabs(result.getDerivative(0) + sin(0.5)) < EPSILON);
        assert(fabs(result.getDerivative(1)) < EPSILON);
        assert(fabs(result.getDerivative(2)) < EPSILON);
    }

    // Test tangent function
    {
        Duals<3, double> x(0.5, {1.0, 0.0, 0.0}); // Value = 0.5, Derivatives = {1.0, 0.0, 0.0}
        Duals<3, double> result = tan(x);

        // Check value
        assert(fabs(result.getValue() - tan(0.5)) < EPSILON);

        // Check derivatives
        double sec_sq = 1 / cos(0.5) / cos(0.5);
        assert(fabs(result.getDerivative(0) - sec_sq) < EPSILON);
        assert(fabs(result.getDerivative(1)) < EPSILON);
        assert(fabs(result.getDerivative(2)) < EPSILON);
    }

    // Test arcsin function
    {
        Duals<3, double> x(0.5, {1.0, 0.0, 0.0}); // Value = 0.5, Derivatives = {1.0, 0.0, 0.0}
        Duals<3, double> result = arcsin(x);

        // Check value
        assert(fabs(result.getValue() - asin(0.5)) < EPSILON);

        // Check derivatives
        double sqrt_val = sqrt(1.0 - 0.5 * 0.5);
        assert(fabs(result.getDerivative(0) - 1.0 / sqrt_val) < EPSILON);
        assert(fabs(result.getDerivative(1)) < EPSILON);
        assert(fabs(result.getDerivative(2)) < EPSILON);
    }

    // Test arccos function
    {
        Duals<3, double> x(0.5, {1.0, 0.0, 0.0}); // Value = 0.5, Derivatives = {1.0, 0.0, 0.0}
        Duals<3, double> result = arccos(x);

        // Check value
        assert(fabs(result.getValue() - acos(0.5)) < EPSILON);

        // Check derivatives
        double sqrt_val = sqrt(1.0 - 0.5 * 0.5);
        assert(fabs(result.getDerivative(0) + 1.0 / sqrt_val) < EPSILON);
        assert(fabs(result.getDerivative(1)) < EPSILON);
        assert(fabs(result.getDerivative(2)) < EPSILON);
    }

    // Test arctan function
    {
        Duals<3, double> x(0.5, {1.0, 0.0, 0.0}); // Value = 0.5, Derivatives = {1.0, 0.0, 0.0}
        Duals<3, double> result = arctan(x);

        // Check value
        assert(fabs(result.getValue() - atan(0.5)) < EPSILON);

        // Check derivatives
        double denom = 1.0 + 0.5 * 0.5;
        assert(fabs(result.getDerivative(0) - 1.0 / denom) < EPSILON);
        assert(fabs(result.getDerivative(1)) < EPSILON);
        assert(fabs(result.getDerivative(2)) < EPSILON);
    }

    cout << "All multi-variable trigonometric function tests passed!" << endl;
}

void testSingleVariableMathFunctions() 
{
    // Test pow function
    Duals<1, float> d_pow(2, 1);
    Duals<1, float> result_pow = pow(d_pow, 3);
    assert(fabs(result_pow.getValue() - pow(2, 3)) < EPSILON);
    assert(fabs(result_pow.getDerivative() - 3 * pow(2, 2)) < EPSILON);

    // Test exp function
    Duals<1, float> d_exp(1, 1);
    Duals<1, float> result_exp = exp(d_exp);
    assert(fabs(result_exp.getValue() - exp(1)) < EPSILON);
    assert(fabs(result_exp.getDerivative() - exp(1)) < EPSILON);

    // Test log function
    Duals<1, float> d_log(2, 1);
    Duals<1, float> result_log = log(d_log);
    assert(fabs(result_log.getValue() - log(2)) < EPSILON);
    assert(fabs(result_log.getDerivative() - 0.5) < EPSILON);

    // Test abs function
    Duals<1, float> d_abs(-3, 1);
    Duals<1, float> result_abs = abs(d_abs);
    assert(fabs(result_abs.getValue() - abs(-3)) < EPSILON);
    assert(fabs(result_abs.getDerivative() - (-1)) < EPSILON);

    // Test sqrt function
    Duals<1, float> d_sqrt(4, 1);
    Duals<1, float> result_sqrt = sqrt(d_sqrt);
    assert(fabs(result_sqrt.getValue() - sqrt(4)) < EPSILON);
    assert(fabs(result_sqrt.getDerivative() - 0.25) < EPSILON);

    cout << "All Single variable math function tests passed!" << endl;
}

void testMultiVariableMathFunctions() 
{
    // Test pow function
    Duals<3, float> d_pow(2, {1, 2, 3});
    Duals<3, float> result_pow = pow(d_pow, 3);
    assert(fabs(result_pow.getValue() - pow(2, 3)) < EPSILON);
    assert(fabs(result_pow.getDerivative(0) - 3 * pow(2, 2)) < EPSILON);
    assert(fabs(result_pow.getDerivative(1) - 3 * 2 * pow(2, 2)) < EPSILON);
    assert(fabs(result_pow.getDerivative(2) - 3 * 3 * pow(2, 2)) < EPSILON);

    // Test exp function
    Duals<3, float> d_exp(1, {1, 2, 3});
    Duals<3, float> result_exp = exp(d_exp);
    assert(fabs(result_exp.getValue() - exp(1)) < EPSILON);
    assert(fabs(result_exp.getDerivative(0) - exp(1)) < EPSILON);
    assert(fabs(result_exp.getDerivative(1) - 2 * exp(1)) < EPSILON);
    assert(fabs(result_exp.getDerivative(2) - 3 * exp(1)) < EPSILON);

    // Test log function
    Duals<3, float> d_log(2, {1, 2, 3});
    Duals<3, float> result_log = log(d_log);
    assert(fabs(result_log.getValue() - log(2)) < EPSILON);
    assert(fabs(result_log.getDerivative(0) - 0.5) < EPSILON);
    assert(fabs(result_log.getDerivative(1) - 1.0) < EPSILON);
    assert(fabs(result_log.getDerivative(2) - 1.5) < EPSILON);

    // Test abs function
    Duals<3, float> d_abs(-3, {1, 2, -3});
    Duals<3, float> result_abs = abs(d_abs);
    assert(fabs(result_abs.getValue() - abs(-3)) < EPSILON);
    assert(fabs(result_abs.getDerivative(0) - (-1)) < EPSILON);
    assert(fabs(result_abs.getDerivative(1) - (-2)) < EPSILON);
    assert(fabs(result_abs.getDerivative(2) - (3)) < EPSILON);

    // Test sqrt function
    Duals<3, float> d_sqrt(4, {1, 2, 3});
    Duals<3, float> result_sqrt = sqrt(d_sqrt);
    assert(fabs(result_sqrt.getValue() - sqrt(4)) < EPSILON);
    assert(fabs(result_sqrt.getDerivative(0) - 0.25) < EPSILON);
    assert(fabs(result_sqrt.getDerivative(1) - 0.5 * 2 / 2) < EPSILON);
    assert(fabs(result_sqrt.getDerivative(2) - 0.5 * 3 / 2) < EPSILON);

    cout << "All Multi-variable math function tests passed!" << endl;
}

void testOutputOperatorSingleVariable() 
{
    // Define dual numbers
    Duals<1, int> a(2, 3);
    Duals<1, int> b(3, 4);

    // Test output operator
    std::stringstream ss;
    ss << a << ", " << b;
    assert(ss.str() == "Value: 2, Derivatives: [3], Value: 3, Derivatives: [4]");

    cout << "Output Operator for single variable passed!" << endl;
}

void testOutputOperatorMultivariable() 
{
    // Define dual numbers
    Duals<3, int> a(2, {3, 4, 5});
    Duals<3, int> b(3, {4, 4, 6});

    // Test output operator
    std::stringstream ss;
    ss << a << ", " << b;
    assert(ss.str() == "Value: 2, Derivatives: [3, 4, 5], Value: 3, Derivatives: [4, 4, 6]");

    cout << "Output Operator for multiple variables passed!" << endl;
}

int main() 
{
    testConstructorsSingleVariable();
    testConstructorsMultivariable();
    testGettersAndSettersSingleVariable();
    testGettersAndSettersMultivariable();
    testSingleVariableArithmeticOperators();
    testMultiVariableArithmeticOperators();
    testSingleVariableComparisonOperators();
    testComparisonOperatorsMultivariable();
    testTrigFunctionsSingleVariable();
    testMultivariableTrigFunctions();
    testSingleVariableMathFunctions();
    testMultiVariableMathFunctions();
    testOutputOperatorSingleVariable();
    testOutputOperatorMultivariable();
    return 0;
}
